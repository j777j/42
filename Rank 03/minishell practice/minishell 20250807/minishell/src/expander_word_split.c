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

static int	is_quoted(const char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len < 2)
		return (0);
	if (arg[0] == '\'' && arg[len - 1] == '\'')
		return (1);
	if (arg[0] == '"' && arg[len - 1] == '"')
		return (1);
	return (0);
}

t_list	*split_expanded_arg(char *expanded_str, const char *original_arg)
{
	t_list	*split_list;
	char	**split_arr;
	int		i;

	if (is_quoted(original_arg) || ft_strchr(original_arg, '='))
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
