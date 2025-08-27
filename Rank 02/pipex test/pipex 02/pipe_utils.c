/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:25:54 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 17:00:21 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" // 包含项目主头文件

/*
** create_pipe
** 创建一个匿名管道，并将其读写端文件描述符存储在提供的数组中。
** 如果管道创建失败，则会调用错误处理函数并退出程序。
** @param pipefd 存储管道读写端文件描述符的整数数组 (pipefd[0]为读端，pipefd[1]为写端)。
** @return void。
*/
void	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		handle_system_error("Error creating pipe");
	}
}

/*
** ft_split_path
** 根据特定分隔符分割字符串，用于解析 PATH 环境变量。
** 这是 ft_split 的一个简化版本，只处理单个字符分隔符。
** @param s 要分割的字符串（例如 PATH 环境变量的值）。
** @param c 分隔符（例如 ':'）。
** @return char** 指向子字符串数组的指针，以 NULL 结尾；失败返回NULL。
*/
char	**ft_split_path(const char *s, char c)
{
	char	**arr;
	size_t	num_words;
	size_t	i;

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
		if (!assign_split_substring(arr, s, get_substring_len_split(s, c), i))
			return (NULL);
		s += get_substring_len_split(s, c);
		i++;
	}
	arr[num_words] = NULL;
	return (arr);
}
