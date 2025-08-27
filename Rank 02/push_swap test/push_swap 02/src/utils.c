/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:43:59 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 07:57:40 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
 * is_sorted: 检查栈是否已经升序排序
 *
 * 功能:
 * 遍历栈中的元素，如果发现前一个元素大于后一个元素，则说明未排序。
 *
 * 参数:
 * stack: 要检查的栈。
 *
 * 返回值:
 * 如果已排序或栈为空/只有一个元素，返回 true。否则返回 false。
 */
bool	is_sorted(t_stack *stack)
{
	int	i;

	if (stack == NULL || stack->stack_size < 2)
		return (true);
	i = 0;
	// 遍历到倒数第二个元素
	while (i < stack->top)
	{
		if (stack->storage[i] > stack->storage[i + 1])
			return (false);
		i++;
	}
	return (true);
}

/*
 * find_max_value: 在栈中找到最大的值
 *
 * 功能:
 * 遍历栈，记录并返回找到的最大值。
 * 这对于 sort_3_numbers 算法特别有用。
 *
 * 参数:
 * stack: 要搜索的栈。
 *
 * 返回值:
 * 栈中的最大值。如果栈为空，返回 INT_MIN。
 */
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

/*
 * find_value_pos: 在栈中查找指定值的索引位置
 *
 * 功能:
 * 遍历栈，找到指定值的索引。
 * 这对于 sort_5_numbers 算法中定位最小值很有用。
 *
 * 参数:
 * stack: 要搜索的栈。
 * value: 要查找的值。
 *
 * 返回值:
 * 如果找到，返回值的索引；如果未找到，返回 -1。
 */
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

/*
 * find_min_value_pos: 在栈中找到最小值的索引位置
 *
 * 功能:
 * 遍历栈，记录并返回找到的最小值的索引。
 *
 * 参数:
 * stack: 要搜索的栈。
 *
 * 返回值:
 * 栈中最小值的索引。如果栈为空，返回 -1。
 */
int	find_min_value_pos(t_stack *stack)
{
	int	min_val;
	int	min_pos;
	int	i;

	if (stack == NULL || stack->stack_size == 0)
		return (-1);
	min_val = stack->storage[0];
	min_pos = 0;
	i = 1;
	while (i < stack->stack_size)
	{
		if (stack->storage[i] < min_val)
		{
			min_val = stack->storage[i];
			min_pos = i;
		}
		i++;
	}
	return (min_pos);
}
