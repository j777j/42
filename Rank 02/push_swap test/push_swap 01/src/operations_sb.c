/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_sb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:27:26 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 14:56:57 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h"

// op_sb 函数：交换栈 B 顶部的两个元素
// 参数: stack - 指向栈 B 的指针
//       print_op - 如果为 true，则打印操作指令 "sb\n"
void	op_sb(t_stack *stack, bool print_op)
{
	int temp; // 临时变量
	// 检查栈是否存在且至少有两个元素
	if (stack == NULL || stack->stack_size < 2)
	{
		return ;
	}
	// 执行交换 (与 op_sa 逻辑相同，只是作用的栈不同)
	temp = stack->storage[stack->top];
	stack->storage[stack->top] = stack->storage[stack->top - 1];
	stack->storage[stack->top - 1] = temp;
	// 打印指令 (如果 print_op 为 true)
	if (print_op == true)
	{
		printf("sb\n"); // 最终请替换为 write(1, "sb\n", 3);
	}
}
