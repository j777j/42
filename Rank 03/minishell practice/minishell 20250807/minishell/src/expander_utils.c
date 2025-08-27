/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:05:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/06 13:30:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

void	append_char_to_word(char **word, char c)
{
	char	*new_word;
	char	str[2];

	if (!word)
		return ;
	str[0] = c;
	str[1] = '\0';
	if (!*word)
	{
		*word = ft_strdup(str);
		return ;
	}
	new_word = ft_strjoin(*word, str);
	free(*word);
	*word = new_word;
}


