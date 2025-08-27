/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:33:16 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 13:40:22 by juwang           ###   ########.fr       */
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

	close(pipe_fds[0]); // 第一个命令不需要管道读端
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		handle_system_error("dup2 infile to stdin failed");
	close(infile_fd); // 原始的 infile_fd 已经不需要了
	if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		handle_system_error("dup2 pipe_write to stdout failed");
	close(pipe_fds[1]); // 原始的 pipe_fds[1] 已经不需要了
	// 查找命令的完整路径
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path) // 如果命令路径未找到
	{
		free_command_args(cmd_args); // 释放命令参数内存
		print_custom_error_and_exit("Command 1 not found or executable.");
	}
	// 执行命令。如果成功，execve 不会返回。
	execve(cmd_path, cmd_args, envp);
	// 如果 execve 返回到这里，说明它失败了（例如：权限问题，或路径虽然找到但不是有效的可执行文件）
	free(cmd_path);                                   // 释放 cmd_path 内存
	free_command_args(cmd_args);                      // 释放命令参数内存
	handle_system_error("Error executing command 1"); // 打印系统错误并退出
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

	close(pipe_fds[1]); // 第二个命令不需要管道写端
	if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
		handle_system_error("dup2 pipe_read to stdin failed");
	close(pipe_fds[0]); // 原始的 pipe_fds[0] 已经不需要了
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		handle_system_error("dup2 outfile to stdout failed");
	close(outfile_fd); // 原始的 outfile_fd 已经不需要了
	// 查找命令的完整路径
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path) // 如果命令路径未找到
	{
		free_command_args(cmd_args); // 释放命令参数内存
		print_custom_error_and_exit("Command 2 not found or executable.");
	}
	// 执行命令。如果成功，execve 不会返回。
	execve(cmd_path, cmd_args, envp);
	// 如果 execve 返回到这里，说明它失败了
	free(cmd_path);                                   // 释放 cmd_path 内存
	free_command_args(cmd_args);                      // 释放命令参数内存
	handle_system_error("Error executing command 2"); // 打印系统错误并退出
}
