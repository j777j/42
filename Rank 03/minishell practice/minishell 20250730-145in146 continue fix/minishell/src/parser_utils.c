/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/24 18:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_exec_cmd(void)
{
	t_exec_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->type = NODE_EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*new_redir_cmd(t_cmd *subcmd, char *file, int mode, int fd)
{
	t_redir_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->type = NODE_REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}

t_cmd	*new_pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->type = NODE_PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*new_seq_cmd(t_cmd *left, t_cmd *right)
{
	t_seq_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->type = NODE_SEQ;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

void	add_arg_to_exec_cmd(t_exec_cmd *ecmd, char *arg)
{
	int		i;
	char	**new_argv;

	i = 0;
	if (ecmd->argv)
		while (ecmd->argv[i])
			i++;
	new_argv = ft_calloc(i + 2, sizeof(char *));
	if (!new_argv)
		return ; // Should handle error more gracefully
	i = 0;
	if (ecmd->argv)
	{
		while (ecmd->argv[i])
		{
			new_argv[i] = ecmd->argv[i];
			i++;
		}
	}
	new_argv[i] = arg;
	new_argv[i + 1] = NULL;
	free(ecmd->argv);
	ecmd->argv = new_argv;
}

void	free_ast(t_cmd *cmd)
{
	t_pipe_cmd	*pcmd;
	t_exec_cmd	*ecmd;
	t_redir_cmd	*rcmd;
	t_seq_cmd	*scmd;
	int			i;

	if (!cmd)
		return ;
	if (cmd->type == NODE_PIPE)
	{
		pcmd = (t_pipe_cmd *)cmd;
		free_ast(pcmd->left);
		free_ast(pcmd->right);
	}
	else if (cmd->type == NODE_SEQ)
	{
		scmd = (t_seq_cmd *)cmd;
		free_ast(scmd->left);
		free_ast(scmd->right);
	}
	else if (cmd->type == NODE_REDIR)
	{
		rcmd = (t_redir_cmd *)cmd;
		free_ast(rcmd->cmd);
		free(rcmd->file);
	}
	else if (cmd->type == NODE_EXEC)
	{
		ecmd = (t_exec_cmd *)cmd;
		i = 0;
		while (ecmd->argv && ecmd->argv[i])
			free(ecmd->argv[i++]);
		free(ecmd->argv);
	}
	free(cmd);
}

t_token_type	peek_type(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (TOKEN_EOF);
	return ((*tokens)->type);
}

void	consume_token(t_token **tokens)
{
	if (tokens && *tokens)
		*tokens = (*tokens)->next;
}