/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	rotate(t_stack *stack)
{
	if (stack->size < 2)
		return ;
	stack->top = stack->top->next;
}

void	op_ra(t_stack *a, bool print)
{
	rotate(a);
	if (print)
		write(1, "ra\n", 3);
}

void	op_rb(t_stack *b, bool print)
{
	rotate(b);
	if (print)
		write(1, "rb\n", 3);
}

void	op_rr(t_stack *a, t_stack *b, bool print)
{
	rotate(a);
	rotate(b);
	if (print)
		write(1, "rr\n", 3);
}