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
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

static void	execute_simple_cmd_in_pipe(t_cmd *cmd, t_shell *shell)
{
	t_list		*redir_list;
	t_exec_cmd	*ecmd;
	t_cmd		*current_cmd;

	redir_list = NULL;
	current_cmd = cmd;
	while (current_cmd && current_cmd->type == NODE_REDIR)
	{
		ft_lstadd_front(&redir_list, ft_lstnew(current_cmd));
		current_cmd = ((t_redir_cmd *)current_cmd)->cmd;
	}
	if (!current_cmd || current_cmd->type != NODE_EXEC)
	{
		// Handle cases like `| > file` which are syntax errors but might pass the parser
		ft_lstclear(&redir_list, NULL);
		exit(0);
	}
	ecmd = (t_exec_cmd *)current_cmd;
	expand_command_args(ecmd, shell);
	if (!apply_redirections(redir_list, shell))
	{
		ft_lstclear(&redir_list, NULL);
		exit(shell->exit_status);
	}
	ft_lstclear(&redir_list, NULL);
	execute_in_child(ecmd, shell);
}

static void	run_pipe_child(int *p, t_cmd *cmd, t_shell *shell, int side)
{
	if (side == 0)
	{
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
		if (cmd->type == NODE_PIPE)
			execute_pipe_cmd((t_pipe_cmd *)cmd, shell);
		else
			execute_simple_cmd_in_pipe(cmd, shell);
	}
	else
	{
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		if (cmd->type == NODE_PIPE)
			execute_pipe_cmd((t_pipe_cmd *)cmd, shell);
		else
			execute_simple_cmd_in_pipe(cmd, shell);
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
	int	status;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		setup_signals(MODE_EXEC);
		if (!apply_redirections(redir_list, shell))
			exit(shell->exit_status);
		execute_in_child(ecmd, shell);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_signals(MODE_PROMPT);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			ft_printf("\n");
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}
