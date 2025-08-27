/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:05:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/01 14:05:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "libft.h"

static void	add_word_to_list(t_list **list, const char *start, int len)
{
	char	*word;

	word = ft_substr(start, 0, len);
	if (word)
		ft_lstadd_back(list, ft_lstnew(word));
}

t_list	*perform_word_splitting(const char *str)
{
	t_list			*list;
	const char		*start;
	t_quote_state	quote_state;

	list = NULL;
	quote_state = QUOTE_NONE;
	while (*str)
	{
		while (*str && isspace(*str))
			str++;
		if (!*str)
			break ;
		start = str;
		while (*str && (quote_state != QUOTE_NONE || !isspace(*str)))
		{
			if (quote_state == QUOTE_NONE && (*str == '\'' || *str == '"'))
				quote_state = (*str == '\'') ? QUOTE_SINGLE : QUOTE_DOUBLE;
			else if ((quote_state == QUOTE_SINGLE && *str == '\'') || \
					(quote_state == QUOTE_DOUBLE && *str == '"'))
				quote_state = QUOTE_NONE;
			str++;
		}
		add_word_to_list(&list, start, str - start);
	}
	return (list);
}
