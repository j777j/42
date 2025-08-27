/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:41:43 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 09:41:50 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	rotate(t_stack *stack)
{
	int	tmp;
	int	i;

	if (stack == NULL || stack->stack_size < 2)
		return ;
	tmp = stack->storage[stack->top];
	i = stack->top;
	while (i > 0)
	{
		stack->storage[i] = stack->storage[i - 1];
		i--;
	}
	stack->storage[0] = tmp;
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
