/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:58:20 by juwang            #+#    #+#             */
/*   Updated: 2025/07/06 15:59:17 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	setup_fd_redirection(int old_fd, int new_fd, const char *message)
{
	if (dup2(old_fd, new_fd) == -1)
		handle_system_error(message);
	close(old_fd);
}

static void	execute_command_in_child(char *cmd_args[], char *envp[])
{
	char	*cmd_path;

	cmd_path = get_command_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_command_args(cmd_args);
		print_custom_error_and_exit("Command not found or executable.");
	}
	execve(cmd_path, cmd_args, envp);
	free(cmd_path);
	free_command_args(cmd_args);
	handle_system_error("Error executing command");
}

void	execute_first_command(int infile_fd, int pipe_fds[2], char *cmd_args[],
		char *envp[])
{
	close(pipe_fds[0]);
	setup_fd_redirection(infile_fd, STDIN_FILENO,
		"dup2 infile to stdin failed");
	setup_fd_redirection(pipe_fds[1], STDOUT_FILENO,
		"dup2 pipe_write to stdout failed");
	execute_command_in_child(cmd_args, envp);
}

void	execute_second_command(int outfile_fd, int pipe_fds[2],
		char *cmd_args[], char *envp[])
{
	close(pipe_fds[1]);
	setup_fd_redirection(pipe_fds[0], STDIN_FILENO,
		"dup2 pipe_read to stdin failed");
	setup_fd_redirection(outfile_fd, STDOUT_FILENO,
		"dup2 outfile to stdout failed");
	execute_command_in_child(cmd_args, envp);
}
