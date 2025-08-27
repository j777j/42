/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:57:30 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 16:45:15 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"    // 包含项目主头文件
#include <sys/wait.h> // 包含 waitpid 函数

/*
** init_pipex_data
** 初始化 t_pipex 结构体，解析命令行参数，并打开输入输出文件。
** 这是主函数的第一步，用于设置所有必要的数据。
** @param data 指向 t_pipex 结构体的指针。
** @param argc 命令行参数数量。
** @param argv 命令行参数数组。
** @param envp 环境变量数组。
** @return void。
*/
void	init_pipex_data(t_pipex *data, int argc, char *argv[], char *envp[])
{
	data->envp = envp;
	check_and_extract_args(data, argc, argv);
	parse_and_open_files(data);
	printf("Input file FD: %d\n", data->infile_fd);
	printf("Output file FD: %d\n", data->outfile_fd);
	printf("Pipe read end FD: %d\n", data->pipe_fds[0]);
	printf("Pipe write end FD: %d\n", data->pipe_fds[1]);
	fflush(stdout);
}

/*
** manage_child_processes
** 负责 fork 两个子进程，并根据其角色调用相应的执行函数。
** @param data 指向 t_pipex 结构体的指针。
** @return void。
*/
void	manage_child_processes(t_pipex *data)
{
	data->pid_cmd1 = fork();
	if (data->pid_cmd1 == -1)
		handle_system_error("Error forking first command process");
	else if (data->pid_cmd1 == 0)
	{
		execute_first_command(data->infile_fd, data->pipe_fds, data->cmd1_args,
			data->envp);
	}
	data->pid_cmd2 = fork();
	if (data->pid_cmd2 == -1)
		handle_system_error("Error forking second command process");
	else if (data->pid_cmd2 == 0)
	{
		execute_second_command(data->outfile_fd, data->pipe_fds,
			data->cmd2_args, data->envp);
	}
}

/*
** parent_cleanup_and_wait
** 负责父进程的文件描述符清理，等待子进程完成，并释放分配的内存。
** @param data 指向 t_pipex 结构体的指针。
** @return void。
*/
void	parent_cleanup_and_wait(t_pipex *data)
{
	close(data->infile_fd);
	close(data->outfile_fd);
	close(data->pipe_fds[0]);
	close(data->pipe_fds[1]);
	waitpid(data->pid_cmd1, NULL, 0);
	waitpid(data->pid_cmd2, NULL, 0);
	free_command_args(data->cmd1_args);
	free_command_args(data->cmd2_args);
}

/*
** main
** Pipex 程序的主入口点。
** 负责调用初始化、进程管理和清理等待的辅助函数。
** @param argc 命令行参数的数量。
** @param argv 命令行参数数组。
** @param envp 环境变量数组。
** @return int 程序退出状态 (0 表示成功，非0表示失败)。
*/
int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;

	init_pipex_data(&data, argc, argv, envp);
	manage_child_processes(&data);
	parent_cleanup_and_wait(&data);
	printf("All child processes completed.\n");
	return (0);
}
