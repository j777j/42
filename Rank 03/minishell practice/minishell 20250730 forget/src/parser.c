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

static t_cmd	*parse_seq(t_token **tokens, t_shell *shell);
static t_cmd	*parse_pipe(t_token **tokens, t_shell *shell);
static t_cmd	*parse_exec(t_token **tokens, t_shell *shell, t_cmd *cmd);
static void		*parser_error(char *s, t_shell *shell, t_cmd *cmd);

t_cmd	*parse_command(t_token **tokens, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = parse_seq(tokens, shell);
	if (peek_type(tokens) != TOKEN_EOF)
	{
		char *base_msg = "minishell: syntax error near unexpected token `";
		char *token_str = (*tokens)->value;
		char *msg1 = ft_strjoin(base_msg, token_str);
		char *final_msg = ft_strjoin(msg1, "'");
		ft_putendl_fd(final_msg, 2);
		free(msg1);
		free(final_msg);
		shell->exit_status = 2;
		free_ast(cmd);
		return (NULL);
	}
	return (cmd);
}

static t_cmd	*parse_seq(t_token **tokens, t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;

	cmd = parse_pipe(tokens, shell);
	if (!cmd)
		return (NULL);
	if (peek_type(tokens) == TOKEN_SEMICOLON)
	{
		consume_token(tokens);
		if (peek_type(tokens) == TOKEN_EOF || peek_type(tokens) == TOKEN_SEMICOLON)
			return (parser_error("Syntax error near unexpected token `;'", shell, cmd));
		right_cmd = parse_seq(tokens, shell);
		if (!right_cmd)
		{
			free_ast(cmd);
			return (NULL);
		}
		cmd = new_seq_cmd(cmd, right_cmd);
	}
	return (cmd);
}

static t_cmd	*parse_pipe(t_token **tokens, t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;

	cmd = parse_exec(tokens, shell, NULL);
	if (!cmd)
		return (NULL);
	if (peek_type(tokens) == TOKEN_PIPE)
	{
		consume_token(tokens);
		if (peek_type(tokens) == TOKEN_EOF || peek_type(tokens) == TOKEN_PIPE)
			return (parser_error("Syntax error near unexpected token `|'", shell, cmd));
		right_cmd = parse_pipe(tokens, shell);
		if (!right_cmd)
		{
			free_ast(cmd);
			return (NULL);
		}
		cmd = new_pipe_cmd(cmd, right_cmd);
	}
	return (cmd);
}

// This is the one-pass parser for a simple command sequence.
static t_cmd	*parse_exec(t_token **tokens, t_shell *shell, t_cmd *cmd)
{
	t_exec_cmd	*ecmd;
	t_cmd		*ret;
	t_token_type type;
    char *file;

    (void)cmd;
	ecmd = (t_exec_cmd *)new_exec_cmd();
	ret = (t_cmd *)ecmd;
	while (peek_type(tokens) != TOKEN_PIPE && peek_type(tokens) != TOKEN_EOF
			&& peek_type(tokens) != TOKEN_SEMICOLON)
	{
		type = peek_type(tokens);
		if (type == TOKEN_WORD)
		{
			add_arg_to_exec_cmd(ecmd, ft_strdup((*tokens)->value));
			consume_token(tokens);
		}
		else
		{
			consume_token(tokens);
			if (peek_type(tokens) != TOKEN_WORD)
			{
				free_ast(ret);
				return (parser_error("Syntax error: expected file after redirection", shell, NULL));
			}
			file = (*tokens)->value;
			(*tokens)->value = NULL; // Avoid double free by lexer
			if (type == TOKEN_REDIR_IN)
				ret = new_redir_cmd(ret, file, O_RDONLY, 0);
			else if (type == TOKEN_REDIR_OUT)
				ret = new_redir_cmd(ret, file, O_WRONLY | O_CREAT | O_TRUNC, 1);
			else if (type == TOKEN_REDIR_APPEND)
				ret = new_redir_cmd(ret, file, O_WRONLY | O_CREAT | O_APPEND, 1);
			else if (type == TOKEN_HEREDOC)
				ret = new_redir_cmd(ret, file, O_HEREDOC, 0);
			else
				free(file);
			consume_token(tokens);
		}
	}
	return (ret);
}

static void	*parser_error(char *s, t_shell *shell, t_cmd *cmd)
{
	ft_putendl_fd(s, 2);
	shell->exit_status = 2;
	free_ast(cmd);
	return (NULL);
}
