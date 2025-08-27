/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:20:57 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 08:35:38 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_stack	*init_stack(int capacity)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (stack == NULL)
	{
		exit(EXIT_FAILURE);
	}
	stack->storage = (int *)malloc(sizeof(int) * capacity);
	if (stack->storage == NULL)
	{
		free(stack);
		exit(EXIT_FAILURE);
	}
	stack->capacity = capacity;
	stack->stack_size = 0;
	stack->top = -1;
	return (stack);
}

void	free_stack(t_stack *stack)
{
	if (stack != NULL)
	{
		if (stack->storage != NULL)
		{
			free(stack->storage);
		}
		free(stack);
	}
}

void	free_stacks(t_stack *a, t_stack *b)
{
	free_stack(a);
	free_stack(b);
}
