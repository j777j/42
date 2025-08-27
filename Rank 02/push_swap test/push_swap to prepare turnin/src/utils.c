/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:37:52 by juwang            #+#    #+#             */
/*   Updated: 2025/07/16 23:02:46 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdio.h>

bool	is_sorted(t_stack *stack)
{
	int	i;

	if (stack == NULL || stack->stack_size < 2)
		return (true);
	i = stack->top;
	while (i > 0)
	{
		if (stack->storage[i] > stack->storage[i - 1])
			return (false);
		i--;
	}
	return (true);
}

int	find_max_value(t_stack *stack)
{
	int	max_val;
	int	i;

	if (stack == NULL || stack->stack_size == 0)
		return (INT_MIN);
	max_val = stack->storage[0];
	i = 1;
	while (i < stack->stack_size)
	{
		if (stack->storage[i] > max_val)
			max_val = stack->storage[i];
		i++;
	}
	return (max_val);
}

int	find_value_pos(t_stack *stack, int value)
{
	int	i;

	if (stack == NULL || stack->stack_size == 0)
		return (-1);
	i = 0;
	while (i < stack->stack_size)
	{
		if (stack->storage[i] == value)
			return (i);
		i++;
	}
	return (-1);
}

int	find_min_value_pos(t_stack *stack)
{
	int	min_val;
	int	min_pos_from_bottom;
	int	i;

	if (stack == NULL || stack->stack_size == 0)
		return (-1);
	min_val = stack->storage[0];
	min_pos_from_bottom = 0;
	i = 1;
	while (i < stack->stack_size)
	{
		if (stack->storage[i] < min_val)
		{
			min_val = stack->storage[i];
			min_pos_from_bottom = i;
		}
		i++;
	}
	return (min_pos_from_bottom);
}
