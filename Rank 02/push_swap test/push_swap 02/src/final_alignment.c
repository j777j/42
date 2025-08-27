/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_alignment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 08:19:56 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 08:20:01 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
 * final_alignment: 对齐 A 栈，使最小值在栈底
 *
 * 功能:
 * 1. 在 A 栈中找到最小值 (等级 0) 的位置。
 * 2. 计算将它旋转到栈底所需的最少步数 (用 ra 还是 rra)。
 * 3. 执行旋转，将最小值移动到栈底 (索引 0)。
 *
 * 注意:
 * 经过此操作后，整个栈就变成了从栈底到栈顶的完全升序排列。
 *
 * 参数:
 * a: 指向 A 栈的指针。
 */
void	final_alignment(t_stack *a)
{
	int	min_pos;
	int	moves_to_bottom;

	// 1. 找到最小值 0 的位置
	min_pos = find_value_pos(a, 0);
	// 2. 计算将它移动到栈底需要多少步
	// 如果它在上半部分，用 ra 更快 (因为 ra 是将栈顶移至栈底)
	if (min_pos >= a->stack_size / 2)
	{
		moves_to_bottom = a->stack_size - min_pos;
		while (moves_to_bottom > 0)
		{
			op_ra(a, true);
			moves_to_bottom--;
		}
	}
	else // 如果它在下半部分，用 rra 更快 (因为 rra 是将栈底移至栈顶)
	{
		moves_to_bottom = min_pos;
		while (moves_to_bottom > 0)
		{
			op_rra(a, true);
			moves_to_bottom--;
		}
	}
}
