/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:00:19 by juwang            #+#    #+#             */
/*   Updated: 2025/07/09 15:26:18 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

void	manage_child_processes(t_pipex *data)
{
	data->pid_cmd1 = fork();
	if (data->pid_cmd1 == -1)
		handle_system_error("Error forking first command process", data);
	else if (data->pid_cmd1 == 0)
	{
		data->cmd_path_to_free = NULL;
		execute_first_command(data);
	}
	data->pid_cmd2 = fork();
	if (data->pid_cmd2 == -1)
		handle_system_error("Error forking second command process", data);
	else if (data->pid_cmd2 == 0)
	{
		data->cmd_path_to_free = NULL;
		execute_second_command(data);
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

	data.cmd1_args = NULL;
	data.cmd2_args = NULL;
	data.infile_fd = -1;
	data.outfile_fd = -1;
	data.pipe_fds[0] = -1;
	data.pipe_fds[1] = -1;
	data.cmd_path_to_free = NULL;
	init_pipex_data(&data, argc, argv, envp);
	manage_child_processes(&data);
	parent_cleanup_and_wait(&data);
	ft_printf("All child processes completed.\n");
	return (0);
}
