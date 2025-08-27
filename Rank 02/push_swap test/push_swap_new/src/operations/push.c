/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	push(t_stack *dest, t_stack *src)
{
	t_node	*node_to_move;

	if (src->size == 0)
		return ;
	node_to_move = src->top;
	if (src->size == 1)
		src->top = NULL;
	else
	{
		src->top = src->top->next;
		node_to_move->prev->next = node_to_move->next;
		node_to_move->next->prev = node_to_move->prev;
	}
	src->size--;
	if (dest->size == 0)
	{
		dest->top = node_to_move;
		node_to_move->next = node_to_move;
		node_to_move->prev = node_to_move;
	}
	else
	{
		node_to_move->next = dest->top;
		node_to_move->prev = dest->top->prev;
		dest->top->prev->next = node_to_move;
		dest->top->prev = node_to_move;
		dest->top = node_to_move;
	}
	dest->size++;
}

void	op_pa(t_stack *a, t_stack *b, bool print)
{
	push(a, b);
	if (print)
		write(1, "pa\n", 3);
}

void	op_pb(t_stack *a, t_stack *b, bool print)
{
	push(b, a);
	if (print)
		write(1, "pb\n", 3);
}