/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:01:12 by juwang            #+#    #+#             */
/*   Updated: 2025/07/12 22:01:01 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_up_resources(t_pipex *data)
{
	if (data->cmd_path_to_free)
	{
		free(data->cmd_path_to_free);
		data->cmd_path_to_free = NULL;
	}
	if (data->cmd1_args)
		free_string_array(data->cmd1_args);
	if (data->cmd2_args)
		free_string_array(data->cmd2_args);
	if (data->infile_fd != -1)
		close(data->infile_fd);
	if (data->outfile_fd != -1)
		close(data->outfile_fd);
	if (data->pipe_fds[0] != -1)
		close(data->pipe_fds[0]);
	if (data->pipe_fds[1] != -1)
		close(data->pipe_fds[1]);
}

void	print_command_error_and_exit(const char *cmd, const char *message,
		t_pipex *data)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	clean_up_resources(data);
	exit(127);
}

void	handle_system_error(const char *message, t_pipex *data)
{
	perror(message);
	clean_up_resources(data);
	exit(EXIT_FAILURE);
}
