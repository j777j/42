/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:08:33 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:57:36 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void		add_token_to_list(t_list **list, char *token);
static t_list	*expand_and_split_arg(char *arg, t_shell *shell);
static void		remove_empty_args(t_list **args);
static void		handle_empty_node(t_list **current, t_list **prev,
					t_list **args);

void	expand_command_args(t_exec_cmd *cmd, t_shell *shell)
{
	t_list	*new_args;
	int		i;
	t_list	*expanded_nodes;

	if (!cmd->argv || !cmd->argv[0])
		return ;
	new_args = NULL;
	i = 0;
	while (cmd->argv[i])
	{
		expanded_nodes = expand_and_split_arg(cmd->argv[i], shell);
		if (expanded_nodes)
		{
			if (new_args == NULL)
				new_args = expanded_nodes;
			else
				ft_lstlast(new_args)->next = expanded_nodes;
		}
		i++;
	}
	remove_empty_args(&new_args);
	ft_split_free(cmd->argv);
	cmd->argv = ft_lst_to_array(new_args);
	ft_lstclear(&new_args, free);
}

static t_list	*expand_and_split_arg(char *arg, t_shell *shell)
{
	t_split_state	state;
	int			i;
	char			*processed_arg;
	char			*home;

	if (arg[0] == '~' && (arg[1] == '\0' || arg[1] == '/'))
	{
		home = get_env_value(shell->env_list, "HOME");
		if (home)
			processed_arg = ft_strjoin(home, arg + 1);
		else
			processed_arg = ft_strdup(arg);
	}
	else
		processed_arg = ft_strdup(arg);
	if (!processed_arg)
		return (NULL);
	state.was_quoted = (processed_arg[0] == '"' && processed_arg[ft_strlen(processed_arg) - 1] == '"')
		|| (processed_arg[0] == '\'' && processed_arg[ft_strlen(processed_arg) - 1] == '\'');
	state.is_assignment = ft_strchr(processed_arg, '=') != NULL;
	state.expanded_str = perform_expansion(processed_arg, shell);
	free(processed_arg);
	if (!state.expanded_str)
		return (NULL);
	if (state.was_quoted || state.is_assignment)
	{
		state.split_list = ft_lstnew(state.expanded_str);
		return (state.split_list);
	}
	state.split_arr = ft_split(state.expanded_str, ' ');
	free(state.expanded_str);
	if (!state.split_arr)
		return (NULL);
	state.split_list = NULL;
	i = 0;
	while (state.split_arr[i])
		add_token_to_list(&state.split_list, state.split_arr[i++]);
	free(state.split_arr);
	return (state.split_list);
}

static void	handle_empty_node(t_list **current, t_list **prev, t_list **args)
{
	if (*prev)
		(*prev)->next = (*current)->next;
	else
		*args = (*current)->next;
	ft_lstdelone(*current, free);
	if (*prev)
		*current = (*prev)->next;
	else
		*current = *args;
}

static void	remove_empty_args(t_list **args)
{
	t_list	*current;
	t_list	*prev;

	current = *args;
	prev = NULL;
	while (current)
	{
		if (ft_strlen((char *)current->content) == 0)
			handle_empty_node(&current, &prev, args);
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

static void	add_token_to_list(t_list **list, char *token)
{
	t_list	*new_node;

	if (!token)
		return ;
	new_node = ft_lstnew(token);
	if (!new_node)
	{
		free(token);
		return ;
	}
	ft_lstadd_back(list, new_node);
}
