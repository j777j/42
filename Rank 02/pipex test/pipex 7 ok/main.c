/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:00:19 by juwang            #+#    #+#             */
/*   Updated: 2025/07/12 22:09:50 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

void	init_pipex_data(t_pipex *data, int argc, char *argv[], char *envp[])
{
	data->envp = envp;
	check_and_extract_args(data, argc, argv);
	parse_and_open_files(data);
}

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
	close(data->pipe_fds[0]);
	close(data->pipe_fds[1]);
}

void	parent_cleanup_and_wait(t_pipex *data)
{
	close(data->infile_fd);
	close(data->outfile_fd);
	waitpid(data->pid_cmd1, NULL, 0);
	waitpid(data->pid_cmd2, NULL, 0);
	free_string_array(data->cmd1_args);
	free_string_array(data->cmd2_args);
}

static void	initialize_pipex_struct(t_pipex *data)
{
	data->cmd1_args = NULL;
	data->cmd2_args = NULL;
	data->infile_fd = -1;
	data->outfile_fd = -1;
	data->pipe_fds[0] = -1;
	data->pipe_fds[1] = -1;
	data->cmd_path_to_free = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;
	int		status_cmd1;
	int		status_cmd2;

	initialize_pipex_struct(&data);
	init_pipex_data(&data, argc, argv, envp);
	manage_child_processes(&data);
	waitpid(data.pid_cmd1, &status_cmd1, 0);
	waitpid(data.pid_cmd2, &status_cmd2, 0);
	parent_cleanup_and_wait(&data);
	ft_printf("All child processes completed.\n");
	if (WIFEXITED(status_cmd2))
		return (WEXITSTATUS(status_cmd2));
	return (EXIT_FAILURE);
}
