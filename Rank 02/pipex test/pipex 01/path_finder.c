/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:39:31 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 13:39:33 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" // 包含项目主头文件

/*
** count_words
** 辅助函数：计算字符串中根据分隔符分割的“单词”数量。
** @param s 要分割的字符串。
** @param c 分隔符字符。
** @return size_t “单词”的数量。
*/
static size_t	count_words(const char *s, char c)
{
	size_t	count;

	int in_word; // 标记是否在单词内部
	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
		{
			in_word = 0; // 遇到分隔符，不在单词内部
		}
		else if (in_word == 0)
		{
			in_word = 1; // 进入新单词
			count++;
		}
		s++;
	}
	return (count);
}

/*
** free_str_array
** 辅助函数：释放一个 char** 数组及其所有子字符串的内存。
** @param arr 要释放的字符串数组。
** @return void。
*/
static void	free_str_array(char **arr)
{
	size_t	i;

	if (!arr) // 检查数组是否为空
		return ;
	i = 0;
	while (arr[i]) // 遍历并释放每个子字符串
	{
		free(arr[i]);
		i++;
	}
	free(arr); // 最后释放数组本身
}

/*
** ft_split_path
** 根据特定分隔符分割字符串，用于解析 PATH 环境变量。
** 这是 ft_split 的一个简化版本，只处理单个字符分隔符。
** @param s 要分割的字符串（例如 PATH 环境变量的值）。
** @param c 分隔符（例如 ':'）。
** @return char** 指向子字符串数组的指针，以 NULL 结尾；失败返回NULL。
*/
static char	**ft_split_path(const char *s, char c)
{
	char	**arr;
	size_t	num_words;
	size_t	i;
	size_t	start;
	size_t	len;

	if (!s) // 字符串为空，直接返回
		return (NULL);
	num_words = count_words(s, c);                           // 计算单词数量
	arr = (char **)malloc(sizeof(char *) * (num_words + 1)); // 分配数组内存
	if (!arr)                                                // 内存分配失败
		return (NULL);
	i = 0;
	len = 0;
	start = 0;
	while (i < num_words) // 遍历每个单词
	{
		while (s[start] == c && s[start] != '\0') // 跳过分隔符
			start++;
		len = 0;
		while (s[start + len] != c && s[start + len] != '\0') // 计算单词长度
			len++;
		arr[i] = (char *)malloc(sizeof(char) * (len + 1)); // 分配单词内存
		if (!arr[i])                                      
			// 单词内存分配失败，释放已分配的内存并返回NULL
		{
			free_str_array(arr);
			return (NULL);
		}
		// 复制单词
		start = 0;
		while (start < len)
		{
			arr[i][start] = s[start]; // 从s的当前位置复制
			start++;
		}
		arr[i][len] = '\0'; // 添加字符串结束符
		i++;
		s += (len + 1); // 移动到下一个单词的起始位置
		start = 0;      // 重置start以在下一个循环中正确工作
	}
	arr[num_words] = NULL; // 数组以 NULL 结尾
	return (arr);
}

/*
** find_path_env_var
** 在环境变量数组 envp 中查找 PATH 环境变量。
** @param envp 环境变量字符串数组。
** @return char* PATH 环境变量的值，如果未找到则返回 NULL。
*/
static char	*find_path_env_var(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] != NULL) // 遍历环境变量数组
	{
		// 检查字符串是否以 "PATH=" 开头
		if (strncmp(envp[i], "PATH=", 5) == 0) // strncmp 比较前5个字符
		{
			return (envp[i] + 5); // 返回 "PATH=" 之后的部分 (即实际路径值)
		}
		i++;
	}
	return (NULL); // 未找到 PATH 环境变量
}

/*
** join_path_and_cmd
** 拼接目录路径和命令名，形成完整的可执行路径。
** 例如：/bin + ls -> /bin/ls
** @param dir 命令所在的目录路径。
** @param cmd 命令的名称。
** @return char* 完整的路径字符串，需要调用者释放；失败返回NULL。
*/
static char	*join_path_and_cmd(const char *dir, const char *cmd)
{
	char	*full_path;
	size_t	dir_len;
	size_t	cmd_len;

	dir_len = 0;
	while (dir[dir_len] != '\0') // 计算目录长度
		dir_len++;
	cmd_len = 0;
	while (cmd[cmd_len] != '\0') // 计算命令长度
		cmd_len++;
	// 分配内存：目录长度 + 1 (for '/') + 命令长度 + 1 (for '\0')
	full_path = (char *)malloc(sizeof(char) * (dir_len + cmd_len + 2));
	if (!full_path) // 内存分配失败
		return (NULL);
	// 拼接字符串
	dir_len = 0; // 重用 dir_len 作为循环计数器
	while (dir[dir_len] != '\0')
	{
		full_path[dir_len] = dir[dir_len];
		dir_len++;
	}
	full_path[dir_len] = '/'; // 添加斜杠
	dir_len++;                // 移动到下一个位置
	cmd_len = 0;              // 重用 cmd_len 作为循环计数器
	while (cmd[cmd_len] != '\0')
	{
		full_path[dir_len + cmd_len] = cmd[cmd_len];
		cmd_len++;
	}
	full_path[dir_len + cmd_len] = '\0'; // 添加字符串结束符
	return (full_path);
}

/*
** get_cmd_path
** 查找命令在 PATH 环境变量中对应的完整可执行路径。
** @param cmd_name 要查找的命令名称。
** @param envp 环境变量数组。
** @return char* 命令的完整路径，需要调用者释放；如果未找到或失败则返回NULL。
*/
char	*get_cmd_path(const char *cmd_name, char *envp[])
{
	char *path_env_val; // PATH 环境变量的值
	char **path_dirs;   // PATH 环境变量分割后的目录数组
	char *full_path;    // 拼接后的完整路径
	int i;              // 循环计数器
	// 如果命令名是绝对路径或相对路径 (如 "/bin/ls" 或 "./my_script")，直接检查
	// 包含 <string.h> 的 strchr 函数
	if (strchr(cmd_name, '/') != NULL)
	{
		if (access(cmd_name, X_OK) == 0) // 检查是否可执行
		{
			// 如果是，复制一份返回，因为 strchr 返回的不是 malloc 的字符串
			full_path = (char *)malloc(sizeof(char) * (strlen(cmd_name) + 1));
			if (!full_path)
				return (NULL);
			strcpy(full_path, cmd_name); // strcpy 需要 #include <string.h>
			return (full_path);
		}
		return (NULL); // 否则返回 NULL
	}
	path_env_val = find_path_env_var(envp); // 查找 PATH 环境变量
	if (!path_env_val)
		return (NULL); // 如果没有 PATH 环境变量，无法查找
	path_dirs = ft_split_path(path_env_val, ':'); // 分割 PATH 环境变量
	if (!path_dirs)
		return (NULL); // 分割失败
	i = 0;
	while (path_dirs[i] != NULL) // 遍历所有 PATH 目录
	{
		full_path = join_path_and_cmd(path_dirs[i], cmd_name); // 拼接完整路径
		if (!full_path)                                        // 拼接失败
		{
			free_str_array(path_dirs);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0) // 检查路径是否可执行
		{
			free_str_array(path_dirs); // 找到后释放目录数组
			return (full_path);        // 返回找到的完整路径
		}
		free(full_path); // 如果不可执行，释放当前拼接的路径
		i++;
	}
	free_str_array(path_dirs); // 所有目录都尝试过后，释放目录数组
	return (NULL);             // 所有目录都未找到可执行命令
}
