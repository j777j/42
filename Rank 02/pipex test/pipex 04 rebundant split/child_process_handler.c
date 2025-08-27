/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:59:09 by juwang            #+#    #+#             */
/*   Updated: 2025/07/06 17:21:21 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	setup_fd_redirection(int old_fd, int new_fd, const char *message,
		t_pipex *data)
{
	if (dup2(old_fd, new_fd) == -1)
		handle_system_error(message, data);
	close(old_fd);
}

static void	execute_command_in_child(char *cmd_args[], char *envp[],
		t_pipex *data)
{
	char	*cmd_path;

	cmd_path = get_command_path(cmd_args[0], envp, data);
	if (!cmd_path)
	{
		print_custom_error_and_exit("Command not found or executable.", data);
	}
	data->cmd_path_to_free = cmd_path;
	execve(cmd_path, cmd_args, envp);
	handle_system_error("Error executing command", data);
}

void	execute_first_command(t_pipex *data)
{
	close(data->pipe_fds[0]);
	setup_fd_redirection(data->infile_fd, STDIN_FILENO,
		"dup2 infile to stdin failed", data);
	setup_fd_redirection(data->pipe_fds[1], STDOUT_FILENO,
		"dup2 pipe_write to stdout failed", data);
	data->cmd_path_to_free = NULL;
	execute_command_in_child(data->cmd1_args, data->envp, data);
}

void	execute_second_command(t_pipex *data)
{
	close(data->pipe_fds[1]);
	setup_fd_redirection(data->pipe_fds[0], STDIN_FILENO,
		"dup2 pipe_read to stdin failed", data);
	setup_fd_redirection(data->outfile_fd, STDOUT_FILENO,
		"dup2 outfile to stdout failed", data);
	data->cmd_path_to_free = NULL;
	execute_command_in_child(data->cmd2_args, data->envp, data);
}
