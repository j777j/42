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

static t_cmd	*parse_pipe(t_token **tokens, t_shell *shell);
static t_cmd	*parse_exec(t_token **tokens, t_shell *shell, t_cmd *cmd);
static void		*parser_error(char *s, t_shell *shell, t_cmd *cmd);

t_cmd	*parse_command(t_token **tokens, t_shell *shell)
{
	t_cmd	*cmd;
	t_token	*head;

	head = *tokens;
	cmd = parse_pipe(tokens, shell);
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

static t_cmd	*parse_pipe(t_token **tokens, t_shell *shell)
{
	t_cmd	*cmd;

	// A pipe is a sequence of execution commands.
	cmd = parse_exec(tokens, shell, NULL);
	if (!cmd)
		return (NULL);
	if (peek_type(tokens) == TOKEN_PIPE)
	{
		consume_token(tokens);
		// After a pipe, we can't have another pipe or EOF.
		if (peek_type(tokens) == TOKEN_EOF || peek_type(tokens) == TOKEN_PIPE)
			return (parser_error("Syntax error near unexpected token `|'", shell, cmd));
		// Recursively parse the right side of the pipe.
		cmd = new_pipe_cmd(cmd, parse_pipe(tokens, shell));
	}
	return (cmd);
}

// This is the new one-pass parser for a simple command sequence.
static t_cmd	*parse_exec(t_token **tokens, t_shell *shell, t_cmd *cmd)
{
	t_exec_cmd	*ecmd;
	t_token_type type;

	// If cmd is NULL, create a new exec node.
	if (cmd == NULL)
		cmd = new_exec_cmd();
	ecmd = (t_exec_cmd *)cmd;

	// Loop through tokens until we hit a pipe or EOF.
	while (peek_type(tokens) != TOKEN_PIPE && peek_type(tokens) != TOKEN_EOF)
	{
		type = peek_type(tokens);
		if (type == TOKEN_WORD)
		{
			// Add the word to the argument list of the current exec command.
			add_arg_to_exec_cmd(ecmd, ft_strdup((*tokens)->value));
			consume_token(tokens);
		}
		else // It's a redirection
		{
			consume_token(tokens); // Consume the redirection token (e.g., '>>', '<')
			if (peek_type(tokens) != TOKEN_WORD)
				return (parser_error("Syntax error: expected file after redirection", shell, cmd));
			
			// Create a new redirection command that wraps the *current* command.
			if (type == TOKEN_REDIR_IN)
				cmd = new_redir_cmd(cmd, ft_strdup((*tokens)->value), O_RDONLY, 0);
			else if (type == TOKEN_REDIR_OUT)
				cmd = new_redir_cmd(cmd, ft_strdup((*tokens)->value), O_WRONLY | O_CREAT | O_TRUNC, 1);
			else if (type == TOKEN_REDIR_APPEND)
				cmd = new_redir_cmd(cmd, ft_strdup((*tokens)->value), O_WRONLY | O_CREAT | O_APPEND, 1);
			else if (type == TOKEN_HEREDOC)
				cmd = new_redir_cmd(cmd, ft_strdup((*tokens)->value), O_HEREDOC, 0);
			consume_token(tokens); // Consume the filename/delimiter
			
			// After a redirection, we might have more arguments or another redirection.
			// We recursively call parse_exec to handle them. The new redir node is passed as `cmd`.
			return (parse_exec(tokens, shell, cmd));
		}
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
