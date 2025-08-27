/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_base_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:46:57 by juwang            #+#    #+#             */
/*   Updated: 2025/07/06 15:47:28 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	count_words_split(const char *s, char c)
{
	size_t	count;
	int		in_substring;

	count = 0;
	in_substring = 0;
	while (*s)
	{
		if (*s == c)
			in_substring = 0;
		else if (in_substring == 0)
		{
			in_substring = 1;
			count++;
		}
		s++;
	}
	return (count);
}

size_t	get_substring_len_split(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

int	alloc_copy_substring(char **arr, const char *s, size_t len, size_t i)
{
	arr[i] = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr[i])
	{
		return (0);
	}
	memcpy(arr[i], s, len);
	arr[i][len] = '\0';
	return (1);
}
