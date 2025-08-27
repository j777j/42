/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:41:23 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 09:41:35 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	push(t_stack *dest, t_stack *src)
{
	int	val_to_push;

	if (src == NULL || src->stack_size == 0)
		return ;
	val_to_push = src->storage[src->top];
	src->top--;
	src->stack_size--;
	dest->top++;
	dest->storage[dest->top] = val_to_push;
	dest->stack_size++;
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
