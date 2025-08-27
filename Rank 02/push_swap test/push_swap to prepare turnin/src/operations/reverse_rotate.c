/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:41:59 by juwang            #+#    #+#             */
/*   Updated: 2025/07/06 13:20:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	reverse_rotate(t_stack *stack)
{
	int	tmp;
	int	i;

	if (stack == NULL || stack->stack_size < 2)
		return ;
	tmp = stack->storage[0];
	i = 0;
	while (i < stack->top)
	{
		stack->storage[i] = stack->storage[i + 1];
		i++;
	}
	stack->storage[stack->top] = tmp;
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
