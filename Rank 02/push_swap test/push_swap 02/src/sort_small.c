/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:53:57 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 08:54:45 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
 * sort_3_numbers: 对 A 栈中刚好 3 个数字进行排序
 * (此函数已正确，保持不变)
 */
void	sort_3_numbers(t_stack *a)
{
	int	max_pos;

	if (is_sorted(a))
		return ;
	max_pos = find_value_pos(a, find_max_value(a));
	if (max_pos == 0)
		op_rra(a, true);
	else if (max_pos == 1)
		op_ra(a, true);
	if (a->storage[a->top] < a->storage[a->top - 1])
		op_sa(a, true);
}

/*
 * sort_5_numbers: 对 A 栈中刚好 5 个数字进行排序 (最终修正版)
 *
 * 修正:
 * 纠正了决定使用 ra 还是 rra 的逻辑。现在，它会根据
 * 元素位置，选择最优的旋转方向。
 */
void	sort_5_numbers(t_stack *a, t_stack *b)
{
	int	min_pos;

	// 将 rank 0 (最小值) 推到 B 栈
	while (a->storage[a->top] != 0)
	{
		min_pos = find_value_pos(a, 0);
		// 如果在下半部分，用 ra 更快
		if (min_pos <= a->stack_size / 2)
			op_ra(a, true);
		else // 如果在上半部分，用 rra 更快
			op_rra(a, true);
	}
	op_pb(a, b, true);
	// 将 rank 1 (第二小值) 推到 B 栈
	while (a->storage[a->top] != 1)
	{
		min_pos = find_value_pos(a, 1);
		// 如果在下半部分，用 ra 更快
		if (min_pos <= a->stack_size / 2)
			op_ra(a, true);
		else // 如果在上半部分，用 rra 更快
			op_rra(a, true);
	}
	op_pb(a, b, true);
	// 排序 A 栈剩下的 3 个数
	sort_3_numbers(a);
	// 将 B 栈的数推回
	op_pa(a, b, true);
	op_pa(a, b, true);
}
