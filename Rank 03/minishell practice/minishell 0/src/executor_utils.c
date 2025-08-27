/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/23 14:15:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_env_by_key(t_list *env_list, const char *key)
{
	t_list	*current;
	t_env	*env_var;
	size_t	key_len;

	current = env_list;
	key_len = ft_strlen(key);
	while (current)
	{
		env_var = (t_env *)current->content;
		if (ft_strlen(env_var->key) == key_len && \
			ft_strncmp(env_var->key, key, key_len) == 0)
			return (env_var);
		current = current->next;
	}
	return (NULL);
}

char	*get_env_value(t_list *env_list, const char *key)
{
	t_env *env_var;

	env_var = get_env_by_key(env_list, key);
	if (env_var)
		return (env_var->value);
	return (NULL);
}

char	**env_list_to_array(t_list *env_list)
{
	char	**array;
	t_list	*current;
	char	*tmp;
	int		i;

	array = ft_calloc(ft_lstsize(env_list) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		t_env *env_var = (t_env *)current->content;
		tmp = ft_strjoin(env_var->key, "=");
		array[i] = ft_strjoin(tmp, env_var->value);
		free(tmp);
		current = current->next;
		i++;
	}
	return (array);
}

static char	*search_in_path(const char *cmd, char *path_env)
{
	char	**paths;
	char	*full_path;
	char	*tmp;
	int		i;

	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			ft_split_free(paths);
			return (full_path);
		}
		free(full_path);
	}
	ft_split_free(paths);
	return (NULL);
}

char	*find_command_path(const char *cmd, t_shell *shell)
{
	char	*path_env;

	if (cmd[0] == '/' || ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_env_value(shell->env_list, "PATH");
	if (!path_env)
		return (NULL);
	return (search_in_path(cmd, path_env));
}

int	is_builtin(const char *name)
{
	if (!name)
		return (0);
	if (ft_strncmp(name, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(name, "env", 4) == 0)
		return (1);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(name, "unset", 6) == 0)
		return (1);
	return (0);
}

int	is_parent_builtin(const char *name)
{
	if (!name)
		return (0);
	if (ft_strncmp(name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(name, "unset", 6) == 0)
		return (1);
	return (0);
}

int	dispatch_builtin(t_exec_cmd *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		shell->exit_status = ft_echo(cmd->argv);
	else if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		shell->exit_status = ft_cd(cmd->argv, shell);
	else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		shell->exit_status = ft_pwd();
	else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		shell->exit_status = ft_env(shell);
	else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		ft_exit(cmd->argv, shell);
	else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		shell->exit_status = ft_export(cmd->argv, shell);
	else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		shell->exit_status = ft_unset(cmd->argv, shell);
	else
		return (0); // Should not happen if is_builtin is correct
	return (1);
}