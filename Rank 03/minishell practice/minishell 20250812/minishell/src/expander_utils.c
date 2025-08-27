/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:05:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/31 14:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "libft.h"

static void	append_char(char **s, char c);
static void	handle_variable_expansion(t_expand_state *state, t_shell *shell);

char	*perform_expansion(const char *arg, t_shell *shell)
{
	t_expand_state	state;

	state.arg = arg;
	state.result = ft_strdup("");
	state.quote_state = 0;
	while (*state.arg)
	{
		if (state.quote_state == 0 && (*state.arg == '\'' || *state.arg == '"'))
			state.quote_state = *state.arg;
		else if (state.quote_state != 0 && *state.arg == state.quote_state)
			state.quote_state = 0;
		else if (*state.arg == '$' && state.quote_state != '\'')
			handle_variable_expansion(&state, shell);
		else
			append_char(&state.result, *state.arg);
		state.arg++;
	}
	return (state.result);
}

static void	handle_variable_expansion(t_expand_state *state, t_shell *shell)
{
	char	*var_name;
	char	*value;
	int		len;

	state->arg++;
	len = 0;
	if (*state->arg == '?')
		len = 1;
	else if (ft_isalpha(*state->arg) || *state->arg == '_')
		while (ft_isalnum(state->arg[len]) || state->arg[len] == '_')
			len++;
	if (len == 0)
	{
		append_char(&state->result, '$');
		return ;
	}
	var_name = ft_substr(state->arg, 0, len);
	if (*state->arg == '?')
		value = ft_itoa(shell->exit_status);
	else
		value = get_env_value(shell->env_list, var_name);
	append_str(&state->result, value);
	if (*state->arg == '?')
		free(value);
	free(var_name);
	state->arg += len - 1;
}

static void	append_char(char **s, char c)
{
	int		len;
	char	*new;

	len = 0;
	if (*s)
		len = ft_strlen(*s);
	new = malloc(len + 2);
	if (!new)
		return ;
	if (*s)
		ft_memcpy(new, *s, len);
	new[len] = c;
	new[len + 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}
