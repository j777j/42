/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:40:32 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 09:41:02 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	swap(t_stack *stack)
{
	int	tmp;

	if (stack == NULL || stack->stack_size < 2)
		return ;
	tmp = stack->storage[stack->top];
	stack->storage[stack->top] = stack->storage[stack->top - 1];
	stack->storage[stack->top - 1] = tmp;
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
