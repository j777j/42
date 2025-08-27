/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/27 17:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		handle_operator(const char *s, int i, t_token **toks);
static int		handle_word(const char *s, int i, t_token **toks, t_shell *sh);
static char		*expand_variable(const char *s, int *i, t_shell *shell);
static char		*append_char(char *s1, char c);

t_token	*lexer(const char *line, t_shell *shell)
{
	t_token	*tokens;
	int		i;
	int		consumed;

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
			consumed = handle_word(line, i, &tokens, shell);
			if (consumed < 0)
			{
				free_tokens(tokens);
				return (NULL);
			}
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

static int	handle_word(const char *s, int i, t_token **toks, t_shell *sh)
{
	char	*word;
	int		start;
	char	quote;
	char	*home_val;

	start = i;
	word = ft_strdup("");
	if (s[i] == '~' && (s[i + 1] == '/' || s[i + 1] == ' ' || s[i + 1] == '\0'))
	{
		home_val = get_env_value(sh->env_list, "HOME");
		if (home_val)
			word = ft_strjoin_free(word, ft_strdup(home_val));
		else
			word = append_char(word, s[i]);
		i++;
	}
	while (s[i] && !ft_strchr(" \t\n\v\f\r<>|;", s[i]))
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
			{
				if (quote == '"' && s[i] == '$')
					word = ft_strjoin_free(word, expand_variable(s, &i, sh));
				else
					word = append_char(word, s[i++]);
			}
			if (s[i] != quote)
			{
				ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
				free(word);
				return (-1);
			}
			i++;
		}
		else if (s[i] == '$')
			word = ft_strjoin_free(word, expand_variable(s, &i, sh));
		else
			word = append_char(word, s[i++]);
	}
	add_token_back(toks, new_token(TOKEN_WORD, word));
	return (i - start);
}

static char	*expand_variable(const char *s, int *i, t_shell *shell)
{
	int		start;
	char	*var_name;
	char	*value;

	(*i)++;
	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}
	start = *i;
	while (ft_isalnum(s[*i]) || s[*i] == '_')
		(*i)++;
	var_name = ft_substr(s, start, *i - start);
	if (!var_name)
		return (ft_strdup(""));
	value = get_env_value(shell->env_list, var_name);
	free(var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static char	*append_char(char *s1, char c)
{
	char	*result;
	int		len;

	len = 0;
	if (s1)
		len = ft_strlen(s1);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	if (s1)
		ft_memcpy(result, s1, len);
	result[len] = c;
	result[len + 1] = '\0';
	free(s1);
	return (result);
}