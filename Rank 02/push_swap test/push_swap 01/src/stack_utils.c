/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:43:59 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 17:26:48 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

bool	is_empty(t_stack *stack)
{
	return (stack == NULL || stack->stack_size == 0);
}

bool	is_sorted(t_stack *stack)
{
	int	i;

	if (is_empty(stack) || stack->stack_size == 1)
	{
		return (true);
	}
	i = 0;
	while (i < stack->stack_size - 1)
	{
		if (stack->storage[i] > stack->storage[i + 1])
		{
			return (false);
		}
		i++;
	}
	return (true);
}

int	max_val_in_stack(t_stack *stack)
{
	int	max_value;
	int	i;

	if (is_empty(stack))
	{
		return (INT_MIN);
	}
	max_value = stack->storage[0];
	i = 1;
	while (i < stack->stack_size)
	{
		if (stack->storage[i] > max_value)
		{
			max_value = stack->storage[i];
		}
		i++;
	}
	return (max_value);
}

void	print_test_stack(t_stack *stack, const char *name)
{
	int i;

	printf("Stack %s (%d/%d): [", name, stack->stack_size, stack->capacity);
	if (stack->stack_size == 0)
	{
		printf("]\n");
		return ;
	}
	i = 0;
	while (i < stack->stack_size)
	{
		printf("%d", stack->storage[i]);
		if (i < stack->stack_size - 1)
			printf(", ");
		i++;
	}
	printf("]\n");
}
