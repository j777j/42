/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:58:08 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 06:48:16 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h" // 包含所有需要的头文件

// find_value_pos 函数：在栈中查找指定值的索引位置
// 参数: stack - 指向要查找的栈的指针
//       value - 要查找的整数值
// 返回值: 如果找到，返回该值的索引；如果未找到，返回 -1。
int	find_value_pos(t_stack *stack, int value)
{
	int i; // 循环索引
	// 检查栈是否为空或无效
	if (stack == NULL || stack->stack_size == 0)
	{
		return (-1); // 栈为空或无效，不可能找到值
	}
	// 从栈底（索引 0）开始遍历到栈顶（索引 stack->stack_size - 1）
	i = 0;
	while (i < stack->stack_size)
	{
		if (stack->storage[i] == value) // 如果当前元素等于目标值
		{
			return (i); // 返回该元素的索引
		}
		i++; // 移动到下一个元素
	}
	return (-1); // 遍历完所有元素仍未找到，返回 -1
}

// get_target_pos_a 函数 (修正版)
int	get_target_pos_a(t_stack *a_stack, int b_val)
{
	int	i;
	int	target_pos;
	int	best_match_val;
	int	max_val;
	int	min_val;

	// 1. 处理 b_val 比 A 栈所有数都大的情况
	//    或处理 A 栈为空的情况
	i = 0;
	max_val = INT_MIN;
	while (i < a_stack->stack_size)
	{
		if (a_stack->storage[i] > max_val)
			max_val = a_stack->storage[i];
		i++;
	}
	if (b_val > max_val || a_stack->stack_size == 0)
	{
		// 目标是全局最小值的位置
		min_val = INT_MAX;
		i = 0;
		while (i < a_stack->stack_size)
		{
			if (a_stack->storage[i] < min_val)
			{
				min_val = a_stack->storage[i];
				target_pos = i;
			}
			i++;
		}
		return (target_pos);
	}
	// 2. 寻找比 b_val 大的数中，最小的那个
	i = 0;
	target_pos = -1;
	best_match_val = INT_MAX;
	while (i < a_stack->stack_size)
	{
		// 如果当前数比 b_val 大，并且比我们之前找到的“最佳匹配”还要小
		if (a_stack->storage[i] > b_val && a_stack->storage[i] < best_match_val)
		{
			best_match_val = a_stack->storage[i];
			target_pos = i;
		}
		i++;
	}
	return (target_pos);
}
// calculate_cost 函数 (修正版)
// 目标：计算将 b_stack[b_pos] 移动到 b_stack 栈顶，
//      并同时将 a_stack 的 a_target_pos 位置移动到 a_stack 栈顶的最小成本
int	calculate_cost(t_stack *a_stack, t_stack *b_stack, int b_pos,
		int a_target_pos)
{
	int	min_cost;
	int	ra_moves;
	int	rra_moves;
	int	rb_moves;
	int	rrb_moves;
	int	cost_rr;
	int	cost_rrr;
	int	cost_ra_rrb;
	int	cost_rra_rb;

	// 1. 计算将 a_target_pos 移动到 A 栈顶的成本
	ra_moves = a_target_pos; // 用 ra 移动的次数
	// 注意：这里的索引是从栈顶 (top) 开始计算的。
	// 如果你的 a_target_pos 是从栈底(0)算的，公式需要调整。
	// 假设 get_target_pos_a 返回的是“目标位置之上”有多少元素，即到栈顶的距离。
	// 为了更清晰，我们直接根据索引计算。
	// 假设 a_target_pos 是从栈底(0)开始的索引。
	if (a_target_pos == 0)
		ra_moves = 0; // 如果目标就是栈底，ra 需要 size-1 次，但我们通常会用 rra
	else
		ra_moves = a_target_pos; // 这是错误的，我们直接在下面更正
	// 正确的计算方法（假设 a_target_pos 是从栈底0开始的索引）
	// 将索引为 a_target_pos 的元素移动到栈顶(索引 a_stack->stack_size - 1)
	ra_moves = a_stack->stack_size - 1 - a_target_pos;
	rra_moves = a_target_pos + 1;
	// 如果目标位置已经是栈顶，则 ra_moves 为 0
	if (a_target_pos == a_stack->stack_size - 1)
	{
		ra_moves = 0;
	}
	// 如果目标位置是栈底, rra_moves 为 1
	if (a_target_pos == 0)
	{
		rra_moves = 1;
	}
	// 2. 计算将 b_pos 移动到 B 栈顶的成本 (同理)
	rb_moves = b_stack->stack_size - 1 - b_pos;
	rrb_moves = b_pos + 1;
	if (b_pos == b_stack->stack_size - 1)
	{
		rb_moves = 0;
	}
	if (b_pos == 0)
	{
		rrb_moves = 1;
	}
	// 3. 计算四种组合的成本
	// 组合1: ra + rb (可用 rr 优化)
	cost_rr = ra_moves;
	if (rb_moves > ra_moves)
		cost_rr = rb_moves;
	// 组合2: rra + rrb (可用 rrr 优化)
	cost_rrr = rra_moves;
	if (rrb_moves > rra_moves)
		cost_rrr = rrb_moves;
	// 组合3: ra + rrb (无优化)
	cost_ra_rrb = ra_moves + rrb_moves;
	// 组合4: rra + rb (无优化)
	cost_rra_rb = rra_moves + rb_moves;
	// 4. 找出最小成本
	min_cost = cost_rr;
	if (cost_rrr < min_cost)
		min_cost = cost_rrr;
	if (cost_ra_rrb < min_cost)
		min_cost = cost_ra_rrb;
	if (cost_rra_rb < min_cost)
		min_cost = cost_rra_rb;
	return (min_cost);
}
