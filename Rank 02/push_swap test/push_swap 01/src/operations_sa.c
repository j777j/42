/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_sa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:27:01 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 14:56:13 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h"

void	op_sa(t_stack *stack, bool print_op)
{
	int	temp;

	if (stack == NULL || stack->stack_size < 2)
		return ;
	temp = stack->storage[stack->top];
	stack->storage[stack->top] = stack->storage[stack->top - 1];
	stack->storage[stack->top - 1] = temp;
	if (print_op == true)
	{
		printf("sa\n");
	}
}
