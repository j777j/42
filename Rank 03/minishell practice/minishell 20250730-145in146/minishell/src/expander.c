/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/31 12:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "libft.h"

static void	add_token_to_list(t_list **list, char *token);
static t_list	*expand_and_split_arg(char *arg, t_shell *shell);
static void	remove_empty_args(t_list **args);

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
			ft_lstadd_back(&new_args, expanded_nodes);
		i++;
	}
	remove_empty_args(&new_args);
	ft_split_free(cmd->argv);
	cmd->argv = ft_lst_to_array(new_args);
	ft_lstclear(&new_args, free);
}

static t_list	*expand_and_split_arg(char *arg, t_shell *shell)
{
	char	*expanded_str;
	t_list	*split_list;
	char	**split_arr;
	int		i;
	int		is_quoted;
	int		is_assignment;

	is_quoted = (arg[0] == '"' && arg[ft_strlen(arg) - 1] == '"') || \
				(arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'');
	is_assignment = ft_strchr(arg, '=') != NULL;
	expanded_str = perform_expansion(arg, shell);
	if (!expanded_str)
		return (NULL);
	if (is_quoted || is_assignment)
	{
		split_list = ft_lstnew(expanded_str);
		return (split_list);
	}
	split_arr = ft_split(expanded_str, ' ');
	free(expanded_str);
	if (!split_arr)
		return (NULL);
	split_list = NULL;
	i = 0;
	while (split_arr[i])
		add_token_to_list(&split_list, split_arr[i++]);
	free(split_arr);
	return (split_list);
}

static void	remove_empty_args(t_list **args)
{
	t_list	*current;
	t_list	*prev;
	t_list	*next;

	current = *args;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (ft_strlen((char *)current->content) == 0)
		{
			if (prev)
				prev->next = next;
			else
				*args = next;
			ft_lstdelone(current, free);
		}
		else
			prev = current;
		current = next;
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
