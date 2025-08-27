/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

bool	is_sorted(t_stack *stack)
{
	t_node	*current;
	int		i;

	if (stack->size <= 1)
		return (true);
	current = stack->top;
	i = 0;
	while (i < stack->size - 1)
	{
		if (current->rank > current->next->rank)
			return (false);
		current = current->next;
		i++;
	}
	return (true);
}

int	get_min_rank_pos(t_stack *stack)
{
	t_node	*current;
	int		min_rank;
	int		pos;
	int		min_pos;
	int		i;

	current = stack->top;
	min_rank = INT_MAX;
	pos = 0;
	min_pos = 0;
	i = 0;
	while (i < stack->size)
	{
		if (current->rank < min_rank)
		{
			min_rank = current->rank;
			min_pos = pos;
		}
		current = current->next;
		pos++;
		i++;
	}
	return (min_pos);
}
