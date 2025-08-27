/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/06/ 11:30:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

int	add_token(t_list **tokens, t_token_type type, char *value, int len)
{
	t_token	*token;
	t_list	*new_node;
	char	*val;

	if (len > 0)
		val = ft_substr(value, 0, len);
	else
		val = ft_strdup(value);
	token = new_token(type, val);
	new_node = ft_lstnew(token);
	ft_lstadd_back(tokens, new_node);
	return (len);
}

void	free_token(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = (t_token *)content;
	free(token->value);
	free(token);
}

void	free_tokens(t_list *tokens)
{
	ft_lstclear(&tokens, free_token);
}
