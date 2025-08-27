/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:53:52 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 17:00:25 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" // 包含项目主头文件

/*
** find_path_env_var
** 在环境变量数组 envp 中查找 PATH 环境变量。
** @param envp 环境变量字符串数组。
** @return char* PATH 环境变量的值，如果未找到则返回 NULL。
*/
char	*find_path_env_var(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			return (envp[i] + 5);
		}
		i++;
	}
	return (NULL);
}

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
** free_str_array
** 释放一个 char** 数组及其所有子字符串的内存。
** @param arr 要释放的字符串数组。
** @return void。
*/
void	free_str_array(char **arr)
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
** get_substring_len_split
** 辅助函数：计算分割子字符串的长度。
** @param s 指向子字符串起始的指针。
** @param c 分隔符字符。
** @return size_t 当前子字符串的长度。
*/
static size_t	get_substring_len_split(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

/*
** assign_split_substring
** 辅助函数：分配内存并复制一个子字符串到数组中。
** @param arr 目标字符串数组。
** @param s 原始字符串的当前位置。
** @param len 子字符串的长度。
** @param i 数组中的索引。
** @return int 成功返回1，失败返回0。
*/
static int	assign_split_substring(char **arr, const char *s, size_t len,
		size_t i)
{
	arr[i] = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr[i])
	{
		free_str_array(arr);
		return (0);
	}
	memcpy(arr[i], s, len);
	arr[i][len] = '\0';
	return (1);
}
