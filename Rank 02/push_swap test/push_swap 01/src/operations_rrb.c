/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rrb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:27:21 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 14:56:40 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h"

// op_rrb 函数：栈 B 中的所有元素向下移动一个位置
// 参数: stack - 指向栈 B 的指针
//       print_op - 如果为 true，则打印操作指令 "rrb\n"
void	op_rrb(t_stack *stack, bool print_op)
{
	int last_value; // 临时变量
	int i;          // 循环索引
	// 检查栈是否存在且至少有两个元素才能旋转
	if (stack == NULL || stack->stack_size < 2)
	{
		return ;
	}
	last_value = stack->storage[0]; // 保存原栈底元素 (索引 0)
	// 将所有元素向上移动一个位置 (复制 op_rra 的核心逻辑)
	i = stack->top;
	while (i > 0)
	{
		stack->storage[i] = stack->storage[i - 1];
		i--;
	}
	// 将原栈底元素放到数组的顶部 (原栈顶的位置)
	stack->storage[0] = last_value;
	// 打印指令 (如果 print_op 为 true)
	if (print_op == true)
	{
		printf("rrb\n"); // 最终请替换为 write(1, "rrb\n", 3);
	}
}
