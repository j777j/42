/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/07 17:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

static void	process_char(char **word_ptr, t_expand_state *state, t_shell *shell);
static void	handle_quotes(char c, t_expand_state *state);
static void	finalize_word(t_expand_state *state);
static void	handle_dollar_sign(char **word_ptr, t_expand_state *state, t_shell *shell);
static void append_str_to_word(char **word, const char *str);

void	expand_and_split_word(char *word, t_shell *shell, t_list **list)
{
	t_expand_state	state;
	char			*word_ptr;

	if (!word)
		return;
	state.result_list = list;
	state.current_word = ft_strdup("");
	state.in_quotes = 0;
	state.in_dquotes = 0;
	word_ptr = word;
	while (*word_ptr)
	{
		process_char(&word_ptr, &state, shell);
	}
	finalize_word(&state);
	free(state.current_word);
}

static void	process_char(char **word_ptr, t_expand_state *state, t_shell *shell)
{
	char c;

	c = **word_ptr;
	if ((c == '\'' && !state->in_dquotes) || (c == '"' && !state->in_quotes))
	{
		handle_quotes(c, state);
		(*word_ptr)++;
		return ;
	}
	if (c == '$' && !state->in_quotes)
	{
		(*word_ptr)++;
		handle_dollar_sign(word_ptr, state, shell);
	}
	else if (ft_isspace(c) && !state->in_quotes && !state->in_dquotes)
	{
		finalize_word(state);
		(*word_ptr)++;
	}
	else
	{
		append_char_to_word(&state->current_word, c);
		(*word_ptr)++;
	}
}

static void	handle_dollar_sign(char **word_ptr, t_expand_state *state, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	int		i;

	if (**word_ptr == '?')
	{
		var_value = ft_itoa(shell->exit_status);
		append_str_to_word(&state->current_word, var_value);
		free(var_value);
		(*word_ptr)++;
		return ;
	}
	i = 0;
	while ((*word_ptr)[i] && (ft_isalnum((*word_ptr)[i]) || (*word_ptr)[i] == '_'))
		i++;
	if (i == 0)
	{
		append_char_to_word(&state->current_word, '$');
		return;
	}
	var_name = ft_substr(*word_ptr, 0, i);
	var_value = get_env_value(shell->env_list, var_name);
	if (var_value)
		append_str_to_word(&state->current_word, var_value);
	free(var_name);
	*word_ptr += i;
}

static void	append_str_to_word(char **word, const char *str)
{
	char *new_word;

	if (!word || !str)
		return;
	if (!*word)
	{
		*word = ft_strdup(str);
		return;
	}
	new_word = ft_strjoin(*word, str);
	free(*word);
	*word = new_word;
}

static void	handle_quotes(char c, t_expand_state *state)
{
	if (c == '\'')
		state->in_quotes = !state->in_quotes;
	else if (c == '"')
		state->in_dquotes = !state->in_dquotes;
}

static void	finalize_word(t_expand_state *state)
{
	if (ft_strlen(state->current_word) > 0)
	{
		ft_lstadd_back(state->result_list, ft_lstnew(state->current_word));
		state->current_word = ft_strdup("");
	}
}