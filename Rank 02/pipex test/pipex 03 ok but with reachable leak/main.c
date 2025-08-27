/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:59:48 by juwang            #+#    #+#             */
/*   Updated: 2025/07/06 16:00:05 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

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

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;

	init_pipex_data(&data, argc, argv, envp);
	manage_child_processes(&data);
	parent_cleanup_and_wait(&data);
	printf("All child processes completed.\n");
	return (0);
}
