/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/22 12:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(const char *s);
static void	print_export(t_shell *shell);
static int	add_or_update_env(char *arg, t_shell *shell);

int	ft_export(char **args, t_shell *shell)
{
	int	i;
	int	ret;

	ret = 0;
	if (!args[1])
	{
		print_export(shell);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (!add_or_update_env(args[i], shell))
			ret = 1;
		i++;
	}
	return (ret);
}

static int	add_or_update_env(char *arg, t_shell *shell)
{
	char	*key;
	char	*value;
	char	*eq_ptr;

	eq_ptr = ft_strchr(arg, '=');
	if (eq_ptr)
	{
		key = ft_substr(arg, 0, eq_ptr - arg);
		value = ft_strdup(eq_ptr + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(key);
		free(value);
		return (0);
	}
	set_env_value(shell, key, value);
	free(key);
	free(value);
	return (1);
}

static void	sort_env_array(t_env **array, int count)
{
	int	i;
	int	j;
	t_env	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strncmp(array[j]->key, array[j + 1]->key, -1) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export(t_shell *shell)
{
	t_list	*current;
	t_env	**env_array;
	int		count;
	int		i;

	count = ft_lstsize(shell->env_list);
	env_array = ft_calloc(count, sizeof(t_env *));
	if (!env_array)
		return ;
	current = shell->env_list;
	i = 0;
	while (current)
	{
		env_array[i++] = (t_env *)current->content;
		current = current->next;
	}
	sort_env_array(env_array, count);
	i = -1;
	while (++i < count)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env_array[i]->key, 1);
		if (env_array[i]->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env_array[i]->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
	}
	free(env_array);
}

static int	is_valid_identifier(const char *s)
{
	if (!s || (!ft_isalpha(*s) && *s != '_'))
		return (0);
	s++;
	while (*s)
	{
		if (!ft_isalnum(*s) && *s != '_')
			return (0);
		s++;
	}
	return (1);
}
