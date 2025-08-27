/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:58:08 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 08:32:40 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
 * push_all_except_three: 将 A 栈中除最大的三个数之外的所有数推到 B 栈
 *
 * 策略:
 * A 栈的总大小为 size。经过标准化后，最大的三个数的等级(rank)是
 * size-1, size-2, 和 size-3。
 * 因此，所有等级小于 (size - 3) 的数都应该被推到 B 栈。
 *
 * 我们遍历 A 栈，如果栈顶元素的等级小于 (size - 3)，就执行 pb。
 * 否则，就执行 ra，把它转到下面，去检查下一个数。
 *
 * 参数:
 * a: 指向 A 栈的指针。
 * b: 指向 B 栈的指针。
 */
void	push_all_except_three(t_stack *a, t_stack *b)
{
	int	size;
	int	pushed_count;
	int	limit;

	size = a->stack_size;
	pushed_count = 0;
	// 我们需要推送 (size - 3) 个数字
	limit = size - 3;
	while (pushed_count < limit)
	{
		// 如果栈顶元素的等级在要推送的范围内
		if (a->storage[a->top] < limit)
		{
			op_pb(a, b, true);
			pushed_count++;
		}
		else
		{
			// 否则，它就是最大的三个数之一，把它转到栈底
			op_ra(a, true);
		}
	}
}
