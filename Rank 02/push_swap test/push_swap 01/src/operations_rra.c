/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:27:19 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 14:56:17 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h"

// op_rra 函数：栈 A 中的所有元素向下移动一个位置
// 参数: stack - 指向栈 A 的指针
//       print_op - 如果为 true，则打印操作指令 "rra\n"
void	op_rra(t_stack *stack, bool print_op)
{
	int last_value; // 临时变量，存储原栈底元素的值
	int i;          // 循环索引
	// 检查栈是否存在且至少有两个元素才能旋转
	if (stack == NULL || stack->stack_size < 2)
	{
		return ;
	}
	last_value = stack->storage[0]; // 保存原栈底元素 (索引 0)
	// 将所有元素向上移动一个位置
	// 从栈底下一个元素 (1) 移动到栈顶 (top)
	// 比如：[1,2,3,4,5] -> rra -> [5,1,2,3,4]
	// 元素 5 (storage[top]) 移动到 storage[top] (不变)
	// 元素 4 (storage[top-1]) 移动到 storage[top]
	// 元素 3 (storage[top-2]) 移动到 storage[top-1] ...
	// 所以循环是从栈顶 (top) 向下遍历到索引 1
	i = stack->top; // 从栈顶开始遍历
	while (i > 0)   // 遍历到索引 1
	{
		stack->storage[i] = stack->storage[i - 1]; // 当前位置被上一个位置的元素覆盖
		i--;
	}
	// 将原栈底元素放到数组的顶部 (原栈顶的位置)
	stack->storage[0] = last_value;
	// 打印指令 (如果 print_op 为 true)
	if (print_op == true)
	{
		printf("rra\n"); // 最终请替换为 write(1, "rra\n", 3);
	}
}
