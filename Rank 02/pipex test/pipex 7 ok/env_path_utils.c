/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:02:43 by juwang            #+#    #+#             */
/*   Updated: 2025/07/12 19:57:35 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_env_var(char *envp[], const char *var_name)
{
	int		i;
	size_t	name_len;

	name_len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, name_len) == 0
			&& envp[i][name_len] == '=')
		{
			return (envp[i] + name_len + 1);
		}
		i++;
	}
	return (NULL);
}

static char	*check_absolute_or_relative_path(const char *cmd_name)
{
	char	*full_path;

	if (ft_strchr(cmd_name, '/') != NULL)
	{
		if (access(cmd_name, X_OK) == 0)
		{
			full_path = (char *)malloc(sizeof(char) * (ft_strlen(cmd_name)
						+ 1));
			if (!full_path)
				return (NULL);
			ft_strlcpy(full_path, cmd_name, ft_strlen(cmd_name) + 1);
			return (full_path);
		}
	}
	return (NULL);
}

static char	*try_path_and_free(char *dir, const char *cmd_name,
		char **path_dirs_to_free)
{
	char	*full_path_with_slash;
	char	*final_full_path;

	full_path_with_slash = ft_strjoin(dir, "/");
	if (!full_path_with_slash)
	{
		free_string_array(path_dirs_to_free);
		return (NULL);
	}
	final_full_path = ft_strjoin(full_path_with_slash, cmd_name);
	free(full_path_with_slash);
	if (!final_full_path)
	{
		free_string_array(path_dirs_to_free);
		return (NULL);
	}
	if (access(final_full_path, X_OK) == 0)
	{
		free_string_array(path_dirs_to_free);
		return (final_full_path);
	}
	free(final_full_path);
	return (NULL);
}

static char	*search_in_path_dirs(char **path_dirs, const char *cmd_name)
{
	char	*found_path;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		found_path = try_path_and_free(path_dirs[i], cmd_name, path_dirs);
		if (found_path)
			return (found_path);
		i++;
	}
	free_string_array(path_dirs);
	return (NULL);
}

char	*get_command_path(const char *cmd_name, char *envp[], t_pipex *data)
{
	char	*path_env_val;
	char	**path_dirs;
	char	*cmd_path;

	cmd_path = check_absolute_or_relative_path(cmd_name);
	if (cmd_path)
		return (cmd_path);
	path_env_val = find_env_var(envp, "PATH");
	if (!path_env_val)
		return (NULL);
	path_dirs = ft_split(path_env_val, ':');
	if (!path_dirs)
	{
		handle_system_error("Memory allocation failed during path split", data);
		return (NULL);
	}
	return (search_in_path_dirs(path_dirs, cmd_name));
}
