/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_ra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:27:12 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 14:57:03 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h"

// op_ra 函数：栈 A 中的所有元素向上移动一个位置
// 参数: stack - 指向栈 A 的指针
//       print_op - 如果为 true，则打印操作指令 "ra\n"
void	op_ra(t_stack *stack, bool print_op)
{
	int first_value; // 临时变量，存储原栈顶元素的值
	int i;           // 循环索引
	// 检查栈是否存在且至少有两个元素才能旋转
	if (stack == NULL || stack->stack_size < 2)
	{
		return ;
	}
	first_value = stack->storage[stack->top]; // 保存原栈顶元素
	// 将所有元素向下移动一个位置
	// 从栈顶下一个元素 (top-1) 移动到栈底 (0)
	// 注意：数组的元素是从 [0] 到 [top]
	// 所以这里的“向上移动”实际上是把所有元素在数组中“往上拷贝”一个位置
	// 比如：[1,2,3,4,5] -> ra -> [2,3,4,5,1]
	// 元素 2 (storage[1]) 移动到 storage[0]
	// 元素 3 (storage[2]) 移动到 storage[1] ...
	// 所以循环是从 storage[1] 复制到 storage[0] 开始
	i = 0;                            // 从栈底开始遍历
	while (i < stack->stack_size - 1) // 遍历到倒数第二个元素
	{
		stack->storage[i] = stack->storage[i + 1]; // 当前位置被下一个位置的元素覆盖
		i++;
	}
	// 将原栈顶元素放到数组的底部 (原索引 0 的位置)
	stack->storage[stack->top] = first_value;
	// 打印指令 (如果 print_op 为 true)
	if (print_op == true)
	{
		printf("ra\n"); // 最终请替换为 write(1, "ra\n", 3);
	}
}
