/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:02:12 by juwang            #+#    #+#             */
/*   Updated: 2025/07/09 15:26:50 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	split_loop_body(char **arr, const char **s, size_t i, char c)
{
	size_t	len;

	while (**s == c && **s != '\0')
		(*s)++;
	len = get_substring_len_split(*s, c);
	if (!alloc_copy_substring(arr, *s, len, i))
	{
		return (0);
	}
	(*s) += len;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	num_words;
	size_t	i;

	if (!s)
		return (NULL);
	num_words = count_words_split(s, c);
	arr = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < num_words)
	{
		if (!split_loop_body(arr, &s, i, c))
		{
			free_string_array(arr);
			return (NULL);
		}
		i++;
	}
	arr[num_words] = NULL;
	return (arr);
}

void	free_string_array(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*string_join(const char *s1, const char *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, s1_len);
	ft_memcpy(new_str + s1_len, s2, s2_len);
	new_str[s1_len + s2_len] = '\0';
	return (new_str);
}

void	free_command_args(char **cmd_args)
{
	size_t	i;

	if (!cmd_args)
		return ;
	i = 0;
	while (cmd_args[i])
	{
		free(cmd_args[i]);
		i++;
	}
	free(cmd_args);
}
