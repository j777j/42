/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:39:31 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 16:47:17 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" // 包含项目主头文件

/*
** check_absolute_or_relative_path
** 辅助函数：检查命令名是否为绝对路径或相对路径，并检查其可执行性。
** @param cmd_name 命令名称。
** @return char* 如果是可执行的绝对/相对路径，返回其副本；否则返回 NULL。
*/
static char	*check_absolute_or_relative_path(const char *cmd_name)
{
	char	*full_path;

	if (strchr(cmd_name, '/') != NULL)
	{
		if (access(cmd_name, X_OK) == 0)
		{
			full_path = (char *)malloc(sizeof(char) * (strlen(cmd_name) + 1));
			if (!full_path)
				return (NULL);
			strcpy(full_path, cmd_name);
			return (full_path);
		}
	}
	return (NULL);
}

/*
** try_path_and_free
** 辅助函数：尝试拼接路径并检查可执行性，然后释放。
** @param dir 当前目录路径。
** @param cmd_name 命令名称。
** @param path_dirs 路径目录数组，用于在失败时释放。
** @return char* 如果找到可执行路径则返回，否则返回 NULL。
*/
static char	*try_path_and_free(char *dir, const char *cmd_name,
		char **path_dirs)
{
	char	*full_path;

	full_path = join_path_and_cmd(dir, cmd_name);
	if (!full_path)
	{
		free_str_array(path_dirs);
		return (NULL);
	}
	if (access(full_path, X_OK) == 0)
	{
		free_str_array(path_dirs);
		return (full_path);
	}
	free(full_path);
}

/*
** search_in_path_dirs
** 辅助函数：在 PATH 环境变量的各个目录中搜索可执行命令。
** @param path_dirs PATH 环境变量分割后的目录数组。
** @param cmd_name 要查找的命令名称。
** @return char* 找到的完整路径；如果未找到或失败则返回 NULL。
*/
static char	*search_in_path_dirs(char **path_dirs, const char *cmd_name)
{
	char	*found_path;
	int		i;

	i = 0;
	while (path_dirs[i] != NULL)
	{
		found_path = try_path_and_free(path_dirs[i], cmd_name, path_dirs);
		if (found_path)
			return (found_path);
		i++;
	}
	free_str_array(path_dirs);
	return (NULL);
}

/*
** get_cmd_path
** 查找命令在 PATH 环境变量中对应的完整可执行路径。
** 首先检查 cmd_name 是否为绝对或相对路径，然后遍历 PATH 目录。
** @param cmd_name 要查找的命令名称。
** @param envp 环境变量数组。
** @return char* 命令的完整路径，需要调用者释放；如果未找到或失败则返回NULL。
*/
char	*get_cmd_path(const char *cmd_name, char *envp[])
{
	char	*path_env_val;
	char	**path_dirs;
	char	*cmd_path;

	cmd_path = check_absolute_or_relative_path(cmd_name);
	if (cmd_path)
		return (cmd_path);
	path_env_val = find_path_env_var(envp);
	if (!path_env_val)
		return (NULL);
	path_dirs = ft_split_path(path_env_val, ':');
	if (!path_dirs)
		return (NULL);
	return (search_in_path_dirs(path_dirs, cmd_name));
}
