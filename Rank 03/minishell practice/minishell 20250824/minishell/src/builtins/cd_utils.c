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

int	do_chdir(char *path, t_shell *shell)
{
	char	cwd[1024];
	char	*last_slash;

	(void)shell;
	// We get the current working directory. If getcwd fails,
	// or if the path is not "..", we fall back to the simple chdir.
	if (ft_strncmp(path, "..", 3) == 0 && getcwd(cwd, sizeof(cwd)) != NULL)
	{
		last_slash = ft_strrchr(cwd, '/');
		// If we are in "/" or "/something", we go to "/"
		if (last_slash == cwd)
			*(last_slash + 1) = '\0';
		// If we are in "/a/b", we go to "/a"
		else if (last_slash != NULL)
			*last_slash = '\0';
		// If chdir with the calculated path fails, print error
		if (chdir(cwd) != 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			return (1);
		}
	}
	else if (chdir(path) != 0) // Standard chdir for all other cases
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}
