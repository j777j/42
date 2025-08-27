/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/06 10:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_operator(const char *s, int i, t_list **tokens);
static int	handle_word(const char *s, int i, t_list **tokens);

/*
** The lexer's job is to turn the raw input string into a list of tokens.
** It should not interpret the tokens (e.g., remove quotes or expand variables).
** It only identifies operators and words, preserving quotes and variable
** syntax as part of the word token's value.
*/
t_list	*lexer(const char *line)
{
	t_list	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			i++;
			continue ;
		}
		if (handle_operator(line, i, &tokens))
		{
			if (line[i] == line[i + 1])
				i += 2;
			else
				i++;
			continue ;
		}
		i += handle_word(line, i, &tokens);
	}
	ft_lstadd_back(&tokens, ft_lstnew(new_token(TOKEN_EOF, ft_strdup("EOF"))));
	return (tokens);
}

static int	handle_operator(const char *s, int i, t_list **tokens)
{
	if (s[i] == '>')
	{
		if (s[i + 1] == '>')
			return (add_token(tokens, TOKEN_REDIR_APPEND, ">>", 2));
		return (add_token(tokens, TOKEN_REDIR_OUT, ">", 1));
	}
	if (s[i] == '<')
	{
		if (s[i + 1] == '<')
			return (add_token(tokens, TOKEN_HEREDOC, "<<", 2));
		return (add_token(tokens, TOKEN_REDIR_IN, "<", 1));
	}
	if (s[i] == '|')
		return (add_token(tokens, TOKEN_PIPE, "|", 1));
	return (0);
}

/*
** A word is a sequence of characters that is not an operator or whitespace.
** Quotes are part of the word and are handled here to ensure that a string
** like "hello world" is treated as a single token.
*/
static int	handle_word(const char *s, int i, t_list **tokens)
{
	int		start;
	char	quote_char;

	start = i;
	quote_char = 0;
	while (s[i])
	{
		if (quote_char)
		{
			if (s[i] == quote_char)
				quote_char = 0;
		}
		else if (s[i] == '\'' || s[i] == '"')
		{
			quote_char = s[i];
		}
		else if (ft_isspace(s[i]) || ft_strchr("<|>", s[i]))
		{
			break;
		}
		i++;
	}
	add_token(tokens, TOKEN_WORD, ft_substr(s, start, i - start), 0);
	return (i - start);
}
