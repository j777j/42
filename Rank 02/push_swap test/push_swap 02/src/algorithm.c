/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:04:09 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 07:55:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
 * run_algorithm: 排序算法的总指挥
 *
 * 功能:
 * 1. 检查栈是否已经排序，如果是，则直接返回。
 * 2. 根据栈中元素的数量，选择最合适的排序策略。
 *
 * 参数:
 * a: 指向 A 栈的指针。
 * b: 指向 B 栈的指针。
 */
void	run_algorithm(t_stack *a, t_stack *b)
{
	int	size;

	size = a->stack_size;
	// 如果栈已经排好序，或者只有一个或零个元素，则无需任何操作。
	if (is_sorted(a) || size <= 1)
	{
		return ;
	}
	// 根据元素数量选择不同的排序函数
	if (size == 2)
		op_sa(a, true);
	else if (size == 3)
		sort_3_numbers(a);
	else if (size == 5)
		sort_5_numbers(a, b);
	else
	{
		// 这里是我们即将实现的核心：处理大量数字的通用算法
		general_sort(a, b);
	}
}
