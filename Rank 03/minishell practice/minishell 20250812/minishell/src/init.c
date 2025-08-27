/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/23 14:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_var(void *content)
{
	t_env	*env_var;

	if (!content)
		return ;
	env_var = (t_env *)content;
	free(env_var->key);
	free(env_var->value);
	free(env_var);
}

void	free_shell(t_shell *shell)
{
	if (shell && shell->env_list)
	{
		ft_lstclear(&shell->env_list, free_env_var);
	}
}

void	set_env_value(t_shell *shell, char *key, char *value)
{
	t_list	*current;
	t_env	*env_var;

	current = shell->env_list;
	while (current)
	{
		env_var = (t_env *)current->content;
		if (ft_strncmp(env_var->key, key, ft_strlen(key) + 1) == 0)
		{
			free(env_var->value);
			if (value)
				env_var->value = ft_strdup(value);
			else
				env_var->value = ft_strdup("");
			return ;
		}
		current = current->next;
	}
	// If not found, create a new one
	env_var = ft_calloc(1, sizeof(t_env));
	if (!env_var)
		return ;
	env_var->key = ft_strdup(key);
	if (value)
		env_var->value = ft_strdup(value);
	else
		env_var->value = ft_strdup("");
	ft_lstadd_back(&shell->env_list, ft_lstnew(env_var));
}

void	init_shell(t_shell *shell, char **envp)
{
	char	*key;
	char	*value;
	char	*eq_ptr;
	int		i;

	shell->env_list = NULL;
	shell->exit_status = 0;
	i = 0;
	while (envp && envp[i])
	{
		eq_ptr = ft_strchr(envp[i], '=');
		if (eq_ptr)
		{
			key = ft_substr(envp[i], 0, eq_ptr - envp[i]);
			value = ft_strdup(eq_ptr + 1);
			set_env_value(shell, key, value);
			free(key);
			free(value);
		}
		i++;
	}
}
