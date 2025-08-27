/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:41:21 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 17:42:51 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" // 包含项目主头文件

/*
** count_splits
** 辅助函数：计算字符串中根据分隔符分割的子字符串数量。
** 专门处理连续分隔符，只计算有效“单词”。
** @param s 要分割的字符串。
** @param c 分隔符字符。
** @return size_t 子字符串的数量。
*/
static size_t	count_splits(const char *s, char c)
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
** get_substring_len_cmd
** 辅助函数：计算命令子字符串的长度。
** @param s 指向子字符串起始的指针。
** @param c 分隔符字符。
** @return size_t 当前子字符串的长度。
*/
static size_t	get_substring_len_cmd(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

/*
** free_command_args
** 释放 parse_command_string 函数分配的 char** 数组及其所有子字符串的内存。
** @param cmd_args 要释放的字符串数组。
** @return void。
*/
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

/*
** allocate_and_copy_arg
** 辅助函数：分配内存并复制一个命令参数到数组中。
** 这是一个关键步骤，确保分配和复制在 25 行限制内。
** @param cmd_args 目标字符串数组。
** @param s 原始字符串的当前位置。
** @param i 数组中的索引。
** @return int 成功返回1，失败返回0。
*/
static int	allocate_and_copy_arg(char **cmd_args, const char *s, size_t i)
{
	size_t	len;

	len = get_substring_len_cmd(s, ' ');
	cmd_args[i] = (char *)malloc(sizeof(char) * (len + 1));
	if (!cmd_args[i])
	{
		free_command_args(cmd_args);
		handle_system_error("Memory allocation failed during command parsing");
		return (0);
	}
	memcpy(cmd_args[i], s, len);
	cmd_args[i][len] = '\0';
	return (1);
}

char	**parse_command_string(const char *cmd_str)
{
	char		**cmd_args;
	size_t		num_args;
	size_t		i;
	const char	*temp_str_ptr;

	cmd_args = init_cmd_args_array(cmd_str, &num_args);
	if (!cmd_args)
		return (NULL);
	i = 0;
	temp_str_ptr = cmd_str;
	while (i < num_args)
	{
		while (*temp_str_ptr == ' ' && *temp_str_ptr != '\0')
			temp_str_ptr++;
		if (!alloc_copy_single_arg(cmd_args, temp_str_ptr, i))
			return (NULL);
		temp_str_ptr += get_substring_len_cmd(temp_str_ptr, ' ');
		i++;
	}
	cmd_args[num_args] = NULL;
	return (cmd_args);
}
