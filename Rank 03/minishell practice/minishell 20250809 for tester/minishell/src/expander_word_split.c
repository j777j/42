/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_word_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 10:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/01 10:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "libft.h"

static int	has_unquoted_spaces(const char *arg)
{
	int	in_quotes;
	int	in_dquotes;

	in_quotes = 0;
	in_dquotes = 0;

	while (*arg)
	{
		if (*arg == '\'' && !in_dquotes)
			in_quotes = !in_quotes;
		else if (*arg == '"' && !in_quotes)
			in_dquotes = !in_dquotes;
		else if (ft_isspace(*arg) && !in_quotes && !in_dquotes)
			return (1);
		arg++;
	}
	return (0);
}

t_list	*split_expanded_arg(char *expanded_str, const char *original_arg)
{
	t_list	*split_list;
	char	**split_arr;
	int		i;

	if (!has_unquoted_spaces(original_arg) || ft_strchr(original_arg, '='))
	{
		split_list = ft_lstnew(expanded_str);
		return (split_list);
	}
	split_arr = ft_split(expanded_str, ' ');
	free(expanded_str);
	if (!split_arr)
		return (NULL);
	split_list = NULL;
	i = 0;

	while (split_arr[i])
	{
		ft_lstadd_back(&split_list, ft_lstnew(split_arr[i]));
		i++;
	}
	free(split_arr);
	return (split_list);
}
