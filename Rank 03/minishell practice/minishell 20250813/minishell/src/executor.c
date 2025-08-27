/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/15 01:30:40 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_parent_builtin(t_exec_cmd *ecmd, t_list *redir_list,
			t_shell *shell);
void	prepare_and_exec_command(t_exec_cmd *cmd, t_shell *shell);

void	execute_ast(t_cmd *cmd, t_shell *shell)
{
	t_seq_cmd	*scmd;

	if (!cmd)
		return ;
	if (cmd->type == NODE_PIPE)
		execute_pipe_cmd((t_pipe_cmd *)cmd, shell);
	else if (cmd->type == NODE_SEQ)
	{
		scmd = (t_seq_cmd *)cmd;
		execute_ast(scmd->left, shell);
		execute_ast(scmd->right, shell);
	}
	else
		execute_simple_command(cmd, shell, 0);
}

void	execute_simple_command(t_cmd *cmd, t_shell *shell, int in_pipe)
{
	t_list		*redir_list;
	t_exec_cmd	*ecmd;
	t_cmd		*current_cmd;

	redir_list = NULL;
	current_cmd = cmd;
	while (current_cmd->type == NODE_REDIR)
	{
		ft_lstadd_front(&redir_list, ft_lstnew(current_cmd));
		current_cmd = ((t_redir_cmd *)current_cmd)->cmd;
	}
	ecmd = (t_exec_cmd *)current_cmd;
	expand_command_args(ecmd, shell);
	if (ecmd->argv[0] && is_parent_builtin(ecmd->argv[0]) && !in_pipe)
		execute_parent_builtin(ecmd, redir_list, shell);
	else
		execute_forked_command(ecmd, redir_list, shell);
	ft_lstclear(&redir_list, NULL);
}

int	apply_redirections(t_list *redir_list, t_shell *shell)
{
	t_list		*current;
	t_redir_cmd	*redir;

	current = redir_list;
	while (current)
	{
		redir = (t_redir_cmd *)current->content;
		if (!handle_single_redirection(redir, shell))
			return (0);
		current = current->next;
	}
	return (1);
}

void	execute_in_child(t_exec_cmd *cmd, t_shell *shell)
{
	if (cmd->argv[0] == NULL)
		exit(0);
	if (is_builtin(cmd->argv[0]))
	{
		dispatch_builtin(cmd, shell);
		exit(shell->exit_status);
	}
	prepare_and_exec_command(cmd, shell);
}
