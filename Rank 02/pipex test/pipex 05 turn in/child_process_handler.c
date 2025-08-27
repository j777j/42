/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:59:09 by juwang            #+#    #+#             */
/*   Updated: 2025/07/12 22:23:26 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	setup_fd_redirection(int old_fd, int new_fd, const char *message,
		t_pipex *data)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		perror(message);
		clean_up_resources(data);
		exit(EXIT_FAILURE);
	}
	close(old_fd);
}

static void	execute_command_in_child(char *cmd_args[], char *envp[],
		t_pipex *data)
{
	char	*cmd_path;

	cmd_path = get_command_path(cmd_args[0], envp, data);
	if (!cmd_path)
	{
		print_command_error_and_exit(cmd_args[0], "command not found", data);
	}
	data->cmd_path_to_free = cmd_path;
	execve(cmd_path, cmd_args, envp);
	handle_system_error("Error executing command", data);
}

void	execute_first_command(t_pipex *data)
{
	close(data->pipe_fds[0]);
	if (data->infile_fd == -1)
	{
		clean_up_resources(data);
		exit(EXIT_FAILURE);
	}
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
	if (data->outfile_fd == -1)
	{
		clean_up_resources(data);
		exit(EXIT_FAILURE);
	}
	setup_fd_redirection(data->pipe_fds[0], STDIN_FILENO,
		"dup2 pipe_read to stdin failed", data);
	setup_fd_redirection(data->outfile_fd, STDOUT_FILENO,
		"dup2 outfile to stdout failed", data);
	data->cmd_path_to_free = NULL;
	execute_command_in_child(data->cmd2_args, data->envp, data);
}
