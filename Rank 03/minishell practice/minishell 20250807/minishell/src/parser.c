/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/24 17:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_pipe(t_list **tokens, t_shell *shell);
static t_cmd	*parse_exec(t_list **tokens, t_shell *shell);
static t_cmd	*parse_redir(t_cmd *cmd, t_list **tokens, t_shell *shell);
static void		*parser_error(char *s, t_shell *shell, t_cmd *cmd);

t_cmd	*parse_command(t_list **tokens, t_shell *shell)
{
	t_list	*head;
	t_cmd	*cmd;

	head = *tokens;
	cmd = parse_pipe(tokens, shell);
	if (peek_type(tokens) != TOKEN_EOF)
	{
		char *base_msg = "minishell: syntax error near unexpected token `";
		char *token_str = ((t_token *)(*tokens)->content)->value;
		char *msg1 = ft_strjoin(base_msg, token_str);
		char *final_msg = ft_strjoin(msg1, "'");
		ft_putendl_fd(final_msg, 2);
		free(msg1);
		free(final_msg);
		shell->exit_status = 2;
		free_ast(cmd);
		return (NULL);
	}
	*tokens = head;
	return (cmd);
}

static t_cmd	*parse_pipe(t_list **tokens, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = parse_exec(tokens, shell);
	if (!cmd)
		return (NULL);
	if (peek_type(tokens) == TOKEN_PIPE)
	{
		consume_token(tokens);
		if (peek_type(tokens) == TOKEN_EOF || peek_type(tokens) == TOKEN_PIPE)
			return (parser_error("Syntax error near unexpected token `|'", shell, cmd));
		cmd = new_pipe_cmd(cmd, parse_pipe(tokens, shell));
	}
	return (cmd);
}

static t_cmd	*parse_exec(t_list **tokens, t_shell *shell)
{
	t_exec_cmd	*cmd;
	t_cmd		*ret;

	// First, check if there's a command to be parsed.
	// If not, it could be just a redirection (e.g., > file)
	if (peek_type(tokens) != TOKEN_WORD &&
		peek_type(tokens) != TOKEN_REDIR_IN &&
		peek_type(tokens) != TOKEN_REDIR_OUT &&
		peek_type(tokens) != TOKEN_REDIR_APPEND &&
		peek_type(tokens) != TOKEN_HEREDOC)
		return (NULL);

	cmd = (t_exec_cmd *)new_exec_cmd();
	ret = (t_cmd *)cmd;

	// First pass for redirections
	ret = parse_redir(ret, tokens, shell);

	while (peek_type(tokens) != TOKEN_PIPE && peek_type(tokens) != TOKEN_EOF)
	{
		if (peek_type(tokens) == TOKEN_WORD)
		{
			add_arg_to_exec_cmd(cmd, ft_strdup(((t_token *)(*tokens)->content)->value));
			consume_token(tokens);
		}
		else // It must be another redirection
		{
			ret = parse_redir(ret, tokens, shell);
		}
	}
	return (ret);
}

static t_cmd	*parse_redir(t_cmd *cmd, t_list **tokens, t_shell *shell)
{
	t_token_type	type;
	char			*file;

	while (peek_type(tokens) == TOKEN_REDIR_IN ||
		   peek_type(tokens) == TOKEN_REDIR_OUT ||
		   peek_type(tokens) == TOKEN_REDIR_APPEND ||
		   peek_type(tokens) == TOKEN_HEREDOC)
	{
		type = peek_type(tokens);
		consume_token(tokens);
		if (peek_type(tokens) != TOKEN_WORD)
		{
			free_ast(cmd);
			return (parser_error("Syntax error: expected file after redirection", shell, NULL));
		}
		file = ft_strdup(((t_token *)(*tokens)->content)->value);
		if (type == TOKEN_REDIR_IN)
			cmd = new_redir_cmd(cmd, file, O_RDONLY, 0);
		else if (type == TOKEN_REDIR_OUT)
			cmd = new_redir_cmd(cmd, file, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (type == TOKEN_REDIR_APPEND)
			cmd = new_redir_cmd(cmd, file, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (type == TOKEN_HEREDOC)
			cmd = new_redir_cmd(cmd, file, O_HEREDOC, 0);
		consume_token(tokens);
	}
	return (cmd);
}

static void	*parser_error(char *s, t_shell *shell, t_cmd *cmd)
{
	ft_putendl_fd(s, 2);
	shell->exit_status = 2;
	free_ast(cmd);
	return (NULL);
}