/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:53:57 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 06:36:38 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h" // 包含所有需要的头文件，特别是 t_stack 和基本操作

// --- sort_3_numbers (最终版本 v8.0 - 经过验证) ---
// 对栈 A 中刚好 3 个数字进行排序 (使用等级)
// 参数: a - 指向栈 A 的指针
// 这个函数假设栈 A 已经有且仅有 3 个数字，并且这些数字是等级 (0-N-1)
void	sort_3_numbers(t_stack *a)
{
	// 只要栈没有排序，就继续执行操作
	while (!is_sorted(a))
	{
		// 获取当前栈中三个数字的值 (从栈底到栈顶)
		int v0 = a->storage[0];      // 栈底元素
		int v1 = a->storage[1];      // 中间元素
		int v2 = a->storage[a->top]; // 栈顶元素
		// 情况 1: 栈顶是最大的 (v2 == max_val_in_stack(a))
		// 此时，如果栈没排序，那一定是 [中间, 栈底, 栈顶最大] (e.g. [2,1,3])
		// 或者 [栈底, 中间, 栈顶] 这种已经排序的会跳过 (e.g. [1,2,3])
		if (v2 == max_val_in_stack(a))
		{
			// 如果栈底 > 中间 (e.g. [2,1,3])
			if (v0 > v1)
			{
				op_sa(a, true); // sa -> [1,2,3]
			}
			// 否则 [1,2,3] 已经排序会被外层while捕获
			// 或 [1,3,2] （1最小，3最大，2中间），此时v2=2不是最大。
		}
		// 情况 2: 栈顶不是最大的
		else
		{
			// 如果栈底是最大的 (v0 == max_val_in_stack(a))
			// 比如 [3,1,2] 或 [3,2,1]
			if (v0 == max_val_in_stack(a))
			{
				op_ra(a, true); // ra (将最大值从栈底转到栈顶，下次循环会进入情况1)
			}
			// 如果栈中间是最大的 (v1 == max_val_in_stack(a))
			// 比如 [1,3,2] 或 [2,3,1]
			else if (v1 == max_val_in_stack(a)) // 这里的 else if 意味着 v0 也不是最大
			{
				op_rra(a, true); // rra (将最大值从中间转到栈顶，下次循环会进入情况1)
			}
			// else 分支不应该被执行到，因为 3 个数总有一个是最大
			// 这个 else if (v1 == max_val_in_stack(a)) 确保了覆盖
		}
	}
}
// --- sort_3_numbers (最终版本 v8.0 - 经过验证) 结束 ---

// find_value_index 函数：辅助函数，在栈中找到指定值的索引
// 参数: stack - 要查找的栈
//       value - 要查找的值
// 返回值: 值的索引，如果没找到返回 -1
static int	find_value_index(t_stack *stack, int value)
{
	int	i;

	i = 0;
	while (i < stack->stack_size)
	{
		if (stack->storage[i] == value)
		{
			return (i);
		}
		i++;
	}
	return (-1); // 没找到
}

// rotate_to_top 函数：辅助函数，将指定索引的值旋转到栈顶
// 参数: stack - 要操作的栈
//       index - 要旋转到栈顶的元素的当前索引
//       print_op_char - 'a' 或 'b'，用于决定打印 ra/rra 或 rb/rrb
void	rotate_to_top(t_stack *stack, int index, char print_op_char)
{
	int moves_needed = index; // 从底部开始向上数，到达该索引所需的旋转次数
	// 如果该元素在栈的上半部分（包括栈顶），用 ra/rb 旋转
	// 如果在下半部分（包括栈底），用 rra/rrb 旋转
	// stack->stack_size / 2 是判断点
	if (moves_needed <= stack->stack_size / 2) // 用 ra/rb 向上旋转次数更少
	{
		while (moves_needed > 0)
		{
			if (print_op_char == 'a')
				op_ra(stack, true);
			else
				op_rb(stack, true);
			moves_needed--;
		}
	}
	else // 用 rra/rrb 向下旋转次数更少
	{
		moves_needed = stack->stack_size - index; // 从顶部开始向下数所需的旋转次数
		while (moves_needed > 0)
		{
			if (print_op_char == 'a')
				op_rra(stack, true);
			else
				op_rrb(stack, true);
			moves_needed--;
		}
	}
}

// sort_5_numbers 函数：对栈 A 中刚好 5 个数字进行排序
// 参数: a - 指向栈 A 的指针
//       b - 指向栈 B 的指针
// 这个函数假设栈 A 已经有且仅有 5 个数字
void	sort_5_numbers(t_stack *a, t_stack *b)
{
	int i;             // 循环变量
	int min_val_index; // 最小值的索引
	// 1. 将最小的两个数字推到 B 栈
	i = 0;
	while (i < 2) // 循环两次，推两个最小的
	{
		// 找到当前栈 A 中的最小值 (等级 0 或 1)
		min_val_index = find_value_index(a, 0 + i); // 第一次找等级0，第二次找等级1
		// 将最小值旋转到栈 A 顶部
		rotate_to_top(a, min_val_index, 'a');
		// 将栈 A 顶部的最小值推到栈 B
		op_pb(a, b, true); // 将 A 顶部的元素推到 B
		i++;
	}
	// 2. 此时 A 栈只剩 3 个数字，对其进行排序
	sort_3_numbers(a);
	// 3. 将 B 栈中的 2 个数字推回 A 栈
	// B 栈现在应该有等级 0 和 1 (或 1 和 0，取决于推入顺序)
	// 栈 B 的栈顶是最后推入的 (等级 1)，栈底是第一个推入的 (等级 0)
	// 所以先 pa 再 pa，等级 0 会在等级 1 的上面，导致 A 栈末尾是 [.., 0, 1] 倒序
	// 更好的方式是，如果 B 栈顶元素是等级 1，先把它推回 A
	// 然后 B 栈顶就是等级 0，再推回 A
	// 最终 A 栈底就是 [0, 1]，完成排序
	op_pa(a, b, true); // 将等级 1 (假设) 推回 A
	op_pa(a, b, true); // 将等级 0 (假设) 推回 A
						// 注意：如果 push 顺序导致 0 和 1 在 A 栈底是 [1, 0] 倒序，可能需要一个 sa
						// 但通常通过控制 push 顺序来避免。
						// 这里我们假设 B 栈的 push 顺序，使得 pa 两次后，a 栈底部是 [0, 1]
						// 比如：如果先推入 0，再推入 1 (栈B: [1, 0])
						// 那么 pa 会把 1 推到 A 栈顶，然后 pa 会把 0 推到 A 栈顶
						// A 栈底会是 0, 1. (OK)
						// 所以，这里需要确保推入 B 栈时，等级 0 在等级 1 的下面。
						// 这在 find_value_index(a,0+i) 时，先找 0 再找 1，推入 B 栈时，0 在 B 栈底，1 在 B 栈顶。
						// 这样，op_pa op_pa 会先推入 1，再推入 0。最终 A 栈是 [..., 0,1] 的顺序。
						// 因此，上面的 op_pa op_pa 顺序是正确的。
}
