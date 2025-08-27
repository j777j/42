/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:27:15 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 14:57:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h"

// op_rb 函数：栈 B 中的所有元素向上移动一个位置
// 参数: stack - 指向栈 B 的指针
//       print_op - 如果为 true，则打印操作指令 "rb\n"
void	op_rb(t_stack *stack, bool print_op)
{
	int first_value; // 临时变量
	int i;           // 循环索引
	// 检查栈是否存在且至少有两个元素才能旋转
	if (stack == NULL || stack->stack_size < 2)
	{
		return ;
	}
	first_value = stack->storage[stack->top]; // 保存原栈顶元素
	// 将所有元素向下移动一个位置 (复制 op_ra 的核心逻辑)
	i = 0;
	while (i < stack->stack_size - 1)
	{
		stack->storage[i] = stack->storage[i + 1];
		i++;
	}
	// 将原栈顶元素放到数组的底部 (原索引 0 的位置)
	stack->storage[stack->top] = first_value;
	// 打印指令 (如果 print_op 为 true)
	if (print_op == true)
	{
		printf("rb\n"); // 最终请替换为 write(1, "rb\n", 3);
	}
}
