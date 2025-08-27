/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/30 23:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_operator(const char *s, int i, t_token **toks);
static int	handle_word(const char *s, int i, t_token **toks);

t_token	*lexer(const char *line, t_shell *shell)
{
	t_token	*tokens;
	int		i;
	int		consumed;

	(void)shell;
	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (ft_strchr(" \t\n\v\f\r", line[i]))
		{
			i++;
			continue ;
		}
		consumed = handle_operator(line, i, &tokens);
		if (consumed > 0)
			i += consumed;
		else
		{
			consumed = handle_word(line, i, &tokens);
			i += consumed;
		}
	}
	add_token_back(&tokens, new_token(TOKEN_EOF, ft_strdup("EOF")));
	return (tokens);
}

static int	handle_operator(const char *s, int i, t_token **toks)
{
	if (s[i] == '>')
	{
		if (s[i + 1] == '>')
		{
			add_token_back(toks, new_token(TOKEN_REDIR_APPEND, ft_strdup(">>")));
			return (2);
		}
		add_token_back(toks, new_token(TOKEN_REDIR_OUT, ft_strdup(">")));
		return (1);
	}
	if (s[i] == '<')
	{
		if (s[i + 1] == '<')
		{
			add_token_back(toks, new_token(TOKEN_HEREDOC, ft_strdup("<<")));
			return (2);
		}
		add_token_back(toks, new_token(TOKEN_REDIR_IN, ft_strdup("<")));
		return (1);
	}
	if (s[i] == '|')
	{
		add_token_back(toks, new_token(TOKEN_PIPE, ft_strdup("|")));
		return (1);
	}
	if (s[i] == ';')
	{
		add_token_back(toks, new_token(TOKEN_SEMICOLON, ft_strdup(";")));
		return (1);
	}
	return (0);
}

static int	handle_word(const char *s, int i, t_token **toks)
{
	int		start;
	char	quote;

	start = i;
	quote = 0;
	while (s[i])
	{
		if (quote == 0 && ft_strchr(" \t\n\v\f\r<>|;", s[i]))
			break ;
		if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
			quote = s[i];
		else if (quote != 0 && s[i] == quote)
			quote = 0;
		i++;
	}
	add_token_back(toks, new_token(TOKEN_WORD, ft_substr(s, start, i - start)));
	return (i - start);
}
