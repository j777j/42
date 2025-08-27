/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:33:16 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 16:35:08 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" // 包含项目主头文件

/*
** execute_first_command
** 为管道中的第一个命令（cmd1）设置子进程环境并执行命令。
** 它将标准输入重定向到 infile_fd，标准输出重定向到管道的写入端。
** @param infile_fd 输入文件的文件描述符。
** @param pipe_fds 包含管道读写端的文件描述符数组。
** @param cmd_args 第一个命令的参数数组 (例如: {"ls", "-l", NULL})。
** @param envp 环境变量数组。
** @return void (如果 execve 成功则不返回，失败则退出)。
*/
void	execute_first_command(int infile_fd, int pipe_fds[2], char *cmd_args[],
		char *envp[])
{
	char	*cmd_path;

	close(pipe_fds[0]);
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		handle_system_error("dup2 infile to stdin failed");
	close(infile_fd);
	if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		handle_system_error("dup2 pipe_write to stdout failed");
	close(pipe_fds[1]);
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_command_args(cmd_args);
		print_custom_error_and_exit("Command 1 not found or executable.");
	}
	execve(cmd_path, cmd_args, envp);
	free(cmd_path);
	free_command_args(cmd_args);
	handle_system_error("Error executing command 1");
}

/*
** execute_second_command
** 为管道中的第二个命令（cmd2）设置子进程环境并执行命令。
** 它将标准输入重定向到管道的读取端，标准输出重定向到 outfile_fd。
** @param outfile_fd 输出文件的文件描述符。
** @param pipe_fds 包含管道读写端的文件描述符数组。
** @param cmd_args 第二个命令的参数数组。
** @param envp 环境变量数组。
** @return void (如果 execve 成功则不返回，失败则退出)。
*/
void	execute_second_command(int outfile_fd, int pipe_fds[2],
		char *cmd_args[], char *envp[])
{
	char	*cmd_path;

	close(pipe_fds[1]);
	if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
		handle_system_error("dup2 pipe_read to stdin failed");
	close(pipe_fds[0]);
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		handle_system_error("dup2 outfile to stdout failed");
	close(outfile_fd);
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_command_args(cmd_args);
		print_custom_error_and_exit("Command 2 not found or executable.");
	}
	execve(cmd_path, cmd_args, envp);
	free(cmd_path);
	free_command_args(cmd_args);
	handle_system_error("Error executing command 2");
}
