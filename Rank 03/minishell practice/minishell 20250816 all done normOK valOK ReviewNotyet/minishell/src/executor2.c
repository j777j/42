/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:09:33 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:57:25 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_pipe_child(int *p, t_cmd *cmd, t_shell *shell, int side);

void	execute_pipe_cmd(t_pipe_cmd *cmd, t_shell *shell)
{
	int		p[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		status;

	if (pipe(p) < 0)
		return ;
	left_pid = fork();
	if (left_pid < 0)
		return ;
	if (left_pid == 0)
		run_pipe_child(p, cmd->left, shell, 0);
	right_pid = fork();
	if (right_pid < 0)
		return ;
	if (right_pid == 0)
		run_pipe_child(p, cmd->right, shell, 1);
	close(p[0]);
	close(p[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}

static void	run_pipe_child(int *p, t_cmd *cmd, t_shell *shell, int side)
{
	if (side == 0)
	{
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
		execute_simple_command(cmd, shell, 1);
	}
	else
	{
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		execute_ast(cmd, shell);
	}
	exit(shell->exit_status);
}

int	handle_heredoc(t_redir_cmd *cmd)
{
	char	*line;
	int		p[2];

	pipe(p);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, cmd->file, ft_strlen(cmd->file) + 1) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		ft_putendl_fd(line, p[1]);
		free(line);
	}
	close(p[1]);
	return (p[0]);
}

void	execute_forked_command(t_exec_cmd *ecmd, t_list *redir_list,
		t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (!apply_redirections(redir_list, shell))
			exit(shell->exit_status);
		execute_in_child(ecmd, shell);
	}
	waitpid(pid, &shell->exit_status, 0);
	if (WIFEXITED(shell->exit_status))
		shell->exit_status = WEXITSTATUS(shell->exit_status);
}
