/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	swap(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (stack->size < 2)
		return ;
	first = stack->top;
	second = first->next;
	first->next = second->next;
	second->prev = first->prev;
	first->prev->next = second;
	second->next->prev = first;
	first->prev = second;
	second->next = first;
	stack->top = second;
}

void	op_sa(t_stack *a, bool print)
{
	swap(a);
	if (print)
		write(1, "sa\n", 3);
}

void	op_sb(t_stack *b, bool print)
{
	swap(b);
	if (print)
		write(1, "sb\n", 3);
}

void	op_ss(t_stack *a, t_stack *b, bool print)
{
	swap(a);
	swap(b);
	if (print)
		write(1, "ss\n", 3);
}