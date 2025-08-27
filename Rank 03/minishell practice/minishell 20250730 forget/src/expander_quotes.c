/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:10:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/01 14:10:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "libft.h"

char	*perform_quote_removal(char *arg)
{
	char	*new_arg;
	int		i;
	int		j;
	char	quote_char;

	new_arg = malloc(ft_strlen(arg) + 1);
	if (!new_arg)
		return (NULL);
	i = 0;
	j = 0;
	quote_char = 0;
	while (arg[i])
	{
		if (quote_char == 0 && (arg[i] == '\'' || arg[i] == '"'))
		{
			quote_char = arg[i];
		}
		else if (quote_char != 0 && arg[i] == quote_char)
		{
			quote_char = 0;
		}
		else
		{
			new_arg[j++] = arg[i];
		}
		i++;
	}
	new_arg[j] = '\0';
	free(arg);
	return (new_arg);
}
