/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:15:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/06 12:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

static void	expand_exec_node(t_exec_cmd *cmd, t_shell *shell);
static void	expand_redir_node(t_redir_cmd *cmd, t_shell *shell);

void	expand_ast(t_cmd *cmd, t_shell *shell)
{
	if (cmd == NULL)
		return ;
	if (cmd->type == NODE_EXEC)
		expand_exec_node((t_exec_cmd *)cmd, shell);
	else if (cmd->type == NODE_REDIR)
		expand_redir_node((t_redir_cmd *)cmd, shell);
	else if (cmd->type == NODE_PIPE)
	{
		expand_ast(((t_pipe_cmd *)cmd)->left, shell);
		expand_ast(((t_pipe_cmd *)cmd)->right, shell);
	}
}

static void	expand_exec_node(t_exec_cmd *cmd, t_shell *shell)
{
	t_list	*expanded_args;
	char	**new_argv;
	int		i;

	if (!cmd->argv || !cmd->argv[0])
		return ;
	expanded_args = NULL;
	i = 0;
	while (cmd->argv[i])
	{
		expand_and_split_word(cmd->argv[i], shell, &expanded_args);
		i++;
	}
	ft_split_free(cmd->argv);
	new_argv = (char **)ft_lst_to_array(expanded_args);
	cmd->argv = new_argv;
	ft_lstclear(&expanded_args, free);
}

static void	expand_redir_node(t_redir_cmd *cmd, t_shell *shell)
{
	t_list	*expanded_filename;
	char	*original_filename;

	original_filename = cmd->file;
	expanded_filename = NULL;
	expand_and_split_word(original_filename, shell, &expanded_filename);
	if (ft_lstsize(expanded_filename) != 1)
	{
		// Handle ambiguous redirect error
		ft_putendl_fd("minishell: ambiguous redirect", 2);
		// This should ideally set an error flag to stop execution
	}
	else
	{
		free(cmd->file);
		cmd->file = ft_strdup((char *)expanded_filename->content);
	}
	ft_lstclear(&expanded_filename, free);
	expand_ast(cmd->cmd, shell);
}
