/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_pb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:27:10 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 17:05:31 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h"

// op_pb 函数：将栈 A 顶部的元素推到栈 B 的顶部
// 参数: a - 指向 A 栈的指针
//       b - 指向 B 栈的指针
//       print_op - 如果为 true，则打印操作指令 "pb\n"
void	op_pb(t_stack *a, t_stack *b, bool print_op)
{
	int value_to_move; // 临时变量，存储从 A 栈取出的值
	// 检查 A 栈是否为空，如果为空则无法移动
	if (a == NULL || a->stack_size == 0)
	{
		return ;
	}
	// 检查 B 栈是否已满
	if (b == NULL || b->stack_size >= b->capacity)
	{
		return ; // B 栈已满，无法推入
	}
	// 1. 从 A 栈弹出元素
	value_to_move = pop_value(a); // 复用 pop_value
	// 2. 将元素推入 B 栈
	push_value(b, value_to_move); // 复用 push_value
	// 打印指令 (如果 print_op 为 true)
	if (print_op == true)
	{
		printf("pb\n"); // 最终请替换为 write(1, "pb\n", 3);
	}
}
