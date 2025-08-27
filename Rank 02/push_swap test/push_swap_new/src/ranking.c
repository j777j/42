/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static t_node	*find_next_min(t_stack *a)
{
	t_node	*current;
	t_node	*min_node;
	int		i;

	current = a->top;
	min_node = NULL;
	i = 0;
	while (i < a->size)
	{
		if (current->rank == -1)
		{
			if (min_node == NULL || current->value < min_node->value)
				min_node = current;
		}
		current = current->next;
		i++;
	}
	return (min_node);
}

void	assign_ranks(t_stack *a)
{
	t_node	*min_node;
	int		rank;
	int		i;

	rank = 0;
	i = 0;
	while (i < a->size)
	{
		min_node = find_next_min(a);
		if (min_node)
			min_node->rank = rank++;
		i++;
	}
}
