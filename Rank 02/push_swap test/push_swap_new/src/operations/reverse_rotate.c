/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	reverse_rotate(t_stack *stack)
{
	if (stack->size < 2)
		return ;
	stack->top = stack->top->prev;
}

void	op_rra(t_stack *a, bool print)
{
	reverse_rotate(a);
	if (print)
		write(1, "rra\n", 4);
}

void	op_rrb(t_stack *b, bool print)
{
	reverse_rotate(b);
	if (print)
		write(1, "rrb\n", 4);
}

void	op_rrr(t_stack *a, t_stack *b, bool print)
{
	reverse_rotate(a);
	reverse_rotate(b);
	if (print)
		write(1, "rrr\n", 4);
}
