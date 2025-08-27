/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:10:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/30 21:10:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	**ft_lst_to_array(t_list *lst)
{
	char	**array;
	int		i;
	t_list	*current;

	array = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!array)
		return (NULL);
	i = 0;
	current = lst;
	while (current)
	{
		array[i] = ft_strdup((char *)current->content);
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	append_str(char **s1, char *s2)
{
	char	*new;

	if (!s2)
		return ;
	if (!*s1)
	{
		*s1 = ft_strdup(s2);
		return ;
	}
	new = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = new;
}
