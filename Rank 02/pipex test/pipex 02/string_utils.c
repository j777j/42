/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:55:32 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 17:55:42 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** count_words
** 辅助函数：计算字符串中根据分隔符分割的“单词”数量。
** 专门处理连续分隔符，只计算有效子字符串。
** @param s 要分割的字符串。
** @param c 分隔符字符。
** @return size_t “单词”的数量。
*/
static size_t	count_words(const char *s, char c)
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

/*
** get_substring_len
** 辅助函数：计算子字符串的长度。
** @param s 指向子字符串起始的指针。
** @param c 分隔符字符。
** @return size_t 当前子字符串的长度。
*/
static size_t	get_substring_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

/*
** ft_split
** 根据特定分隔符分割字符串。
** @param s 要分割的字符串。
** @param c 分隔符。
** @return char** 指向子字符串数组的指针，以 NULL 结尾；失败返回NULL。
*/
char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	num_words;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	num_words = count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < num_words)
	{
		while (*s == c && *s != '\0')
			s++;
		len = get_substring_len(s, c);
		arr[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!arr[i])
		{
			free_string_array(arr);
			return (NULL);
		}
		memcpy(arr[i], s, len);
		arr[i][len] = '\0';
		s += len;
		i++;
	}
	arr[num_words] = NULL;
	return (arr);
}

/*
** free_string_array
** 释放 char** 字符串数组及其所有子字符串的内存。
** @param arr 要释放的字符串数组。
** @return void。
*/
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

/*
** string_join
** 拼接两个字符串，创建一个新的合并字符串。
** @param s1 第一个字符串。
** @param s2 第二个字符串。
** @return char* 拼接后的新字符串，需要调用者释放；失败返回NULL。
*/
char	*string_join(const char *s1, const char *s2)
{
	char *new_str;
	size_t s1_len;
	size_t s2_len;

	s1_len = strlen(s1);
	s2_len = strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new_str)
		return (NULL);
	memcpy(new_str, s1, s1_len);
	memcpy(new_str + s1_len, s2, s2_len);
	new_str[s1_len + s2_len] = '\0';
	return (new_str);
}
