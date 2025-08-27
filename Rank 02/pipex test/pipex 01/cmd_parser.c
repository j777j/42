/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:41:21 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 13:41:32 by juwang           ###   ########.fr       */
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

	int in_substring; // 标记是否在有效子字符串内部
	count = 0;
	in_substring = 0;
	while (*s)
	{
		if (*s == c)
		{
			in_substring = 0; // 遇到分隔符，离开子字符串
		}
		else if (in_substring == 0)
		{
			in_substring = 1; // 进入新子字符串
			count++;
		}
		s++;
	}
	return (count);
}

/*
** get_substring_len
** 辅助函数：计算当前子字符串的长度。
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
** free_cmd_array_and_exit
** 辅助函数：在解析失败时，释放已分配的 char** 数组并退出程序。
** 这是一个内部错误处理，用于内存分配失败。
** @param arr 要释放的字符串数组。
** @return void。
*/
static void	free_cmd_array_and_exit(char **arr)
{
	size_t	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
	// 这里调用 print_custom_error_and_exit 或 handle_system_error
	// 因为这通常是内存分配失败，属于系统错误范畴
	handle_system_error("Memory allocation failed during command parsing");
}

/*
** parse_command_string
** 将一个命令字符串（如 "ls -l"）分割成一个字符串数组（如 {"ls", "-l", NULL}）。
** 使用空格作为分隔符。
** @param cmd_str 要解析的命令字符串。
** @return char** 指向子字符串数组的指针，以 NULL 结尾；如果内存分配失败则退出。
*/
char	**parse_command_string(const char *cmd_str)
{
	char	**cmd_args;
	size_t	num_args;
	size_t	i;
	size_t	len;
	size_t	j;

	if (!cmd_str) // 检查输入字符串是否为空
		return (NULL);
	num_args = count_splits(cmd_str, ' ');                       // 计算参数数量
	cmd_args = (char **)malloc(sizeof(char *) * (num_args + 1)); // 分配数组内存
	if (!cmd_args)
		handle_system_error("Failed to allocate memory for command arguments");
			// 内存分配失败，退出
	i = 0;
	while (i < num_args) // 遍历每个参数
	{
		while (*cmd_str == ' ' && *cmd_str != '\0') // 跳过前导空格
			cmd_str++;
		len = get_substring_len(cmd_str, ' '); // 获取当前参数长度
		cmd_args[i] = (char *)malloc(sizeof(char) * (len + 1)); // 分配参数字符串内存
		if (!cmd_args[i])
			free_cmd_array_and_exit(cmd_args); // 内存分配失败，释放已分配内存并退出
		// 复制参数字符串
		// 注意：这里手动复制，因为 strncpy 行为复杂，而 memcpy 需要长度
		j = 0;
		while (j < len)
		{
			cmd_args[i][j] = cmd_str[j];
			j++;
		}
		cmd_args[i][len] = '\0'; // 添加字符串结束符
		cmd_str += len; // 移动到当前参数的末尾
		i++;
	}
	cmd_args[num_args] = NULL; // 数组以 NULL 结尾
	return (cmd_args);
}

/*
** free_command_args
** 释放 parse_command_string 函数分配的 char** 数组及其所有子字符串的内存。
** @param cmd_args 要释放的字符串数组。
** @return void。
*/
void	free_command_args(char **cmd_args)
{
	size_t i;

	if (!cmd_args) // 检查数组是否为空
		return ;
	i = 0;
	while (cmd_args[i]) // 遍历并释放每个子字符串
	{
		free(cmd_args[i]);
		i++;
	}
	free(cmd_args); // 最后释放数组本身
}
