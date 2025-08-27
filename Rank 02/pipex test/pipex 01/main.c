/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:57:30 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 13:46:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"    // 包含项目主头文件
#include <sys/wait.h> // 包含 waitpid 函数

// 移除以下两行，它们现在在 pipex.h 中声明了
// char    **parse_command_string(const char *cmd_str);
// void    free_command_args(char **cmd_args);

int	main(int argc, char *argv[], char *envp[])
{
	const char	*infile_name;
	const char	*outfile_name;
	char		*cmd1_str;
	char		*cmd2_str;
	char		**cmd1_args;
	char		**cmd2_args;
	int			infile_fd;
	int			outfile_fd;
	int			pipe_fds[2];
	pid_t		pid_cmd1;
	pid_t		pid_cmd2;

	// (void)envp; // envp 现在在 get_cmd_path 和 execve 中使用了，所以不再需要 (void)
	if (argc != 5)
	{
		printf("Usage: ./pipex infile command1 command2 outfile\n");
		print_custom_error_and_exit("Incorrect number of arguments.");
	}
	infile_name = argv[1];
	cmd1_str = argv[2];
	cmd2_str = argv[3];
	outfile_name = argv[4];
	cmd1_args = parse_command_string(cmd1_str);
	if (!cmd1_args)
		print_custom_error_and_exit("Failed to parse command 1.");
	cmd2_args = parse_command_string(cmd2_str);
	if (!cmd2_args)
	{
		free_command_args(cmd1_args);
		print_custom_error_and_exit("Failed to parse command 2.");
	}
	infile_fd = open_infile(infile_name);
	outfile_fd = open_outfile(outfile_name);
	create_pipe(pipe_fds);
	// --- 创建第一个子进程 (执行 cmd1) ---
	pid_cmd1 = fork();
	if (pid_cmd1 == -1)
	{
		handle_system_error("Error forking first command process");
	}
	else if (pid_cmd1 == 0) // 第一个子进程
	{
		execute_first_command(infile_fd, pipe_fds, cmd1_args, envp);
	}
	// --- 创建第二个子进程 (执行 cmd2) ---
	pid_cmd2 = fork();
	if (pid_cmd2 == -1)
	{
		handle_system_error("Error forking second command process");
	}
	else if (pid_cmd2 == 0) // 第二个子进程
	{
		execute_second_command(outfile_fd, pipe_fds, cmd2_args, envp);
	}
	// --- 父进程逻辑 ---
	close(infile_fd);
	close(outfile_fd);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(pid_cmd1, NULL, 0);
	waitpid(pid_cmd2, NULL, 0);
	free_command_args(cmd1_args);
	free_command_args(cmd2_args);
	printf("All child processes completed.\n");
	return (0);
}
