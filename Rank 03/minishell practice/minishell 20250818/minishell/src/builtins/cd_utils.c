/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:01:43 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:55:47 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_path(t_shell *shell)
{
	char	*path;

	path = get_env_value(shell->env_list, "HOME");
	if (!path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	return (path);
}

char	*get_cd_path(char **args, t_shell *shell)
{
	if (args[1] == NULL)
		return (get_home_path(shell));
	return (args[1]);
}

static void	update_env_vars(t_shell *shell)
{
	char	cwd[1024];
	char	*old_pwd;

	old_pwd = get_env_value(shell->env_list, "PWD");
	if (old_pwd)
		set_env_value(shell, "OLDPWD", old_pwd);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		set_env_value(shell, "PWD", cwd);
	else
	{
		// In case of getcwd failure (e.g., no permission),
		// we don't update PWD. Bash has more complex behavior,
		// but this is a reasonable fallback for minishell.
		ft_putendl_fd("cd: error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or directory", 2);
	}
}

int	do_chdir(char *path, t_shell *shell)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	update_env_vars(shell);
	return (0);
}
