/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:33:44 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 17:05:15 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h" // 包含所有需要的头文件

// 辅助函数：从源栈弹出一个元素，并返回该值
// 注意：这个函数会修改源栈的 top 和 stack_size
// 这是一个内部辅助函数，通常不会直接作为 push_swap 指令被外部调用
int	pop_value(t_stack *stack)
{
	int value; // 临时变量，存储被弹出的值
	if (stack == NULL || stack->stack_size == 0)
	{
		// 错误处理，或者返回一个特殊值表示失败
		// 对于 Push Swap 挑战，通常保证不会从空栈 pop
		return (INT_MIN); // 返回整数最小值作为错误指示，需要包含 <limits.h>
	}
	value = stack->storage[stack->top]; // 获取栈顶元素的值
	stack->top--;                       // 栈顶索引向下移动
	stack->stack_size--;                // 栈大小减一
	return (value);
}

// 辅助函数：将一个值推入目标栈的顶部
// 注意：这个函数会修改目标栈的 top 和 stack_size
// 并且可能需要重新分配 storage 数组大小，如果容量不足。
// 但在 Push Swap 中，通常在初始化时就分配好最大容量。
// 这里假设 storage 数组有足够的空间。
void	push_value(t_stack *stack, int value)
{
	if (stack == NULL || stack->stack_size >= stack->capacity)
	{
		// 错误处理：栈已满，无法推入
		// 在 Push Swap 中，A 和 B 栈的总容量通常是固定的
		return ;
	}
	stack->top++;                       // 栈顶索引向上移动
	stack->storage[stack->top] = value; // 将值放入新的栈顶位置
	stack->stack_size++;                // 栈大小加一
}
