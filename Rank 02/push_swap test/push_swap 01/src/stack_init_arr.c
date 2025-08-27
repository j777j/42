/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:20:57 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 18:43:09 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h" // 包含所有需要的头文件，特别是 t_stack

// init_stack_arr 函数：初始化一个数组栈结构体
// 参数: capacity - 栈的最大容量
// 返回值: 指向新初始化的 t_stack 结构体的指针
t_stack	*init_stack_arr(int capacity)
{
	t_stack *stack; // 声明一个栈指针
	int i;          // 声明循环变量
	// 1. 为 t_stack 结构体本身分配内存
	stack = (t_stack *)malloc(sizeof(t_stack));
	if (stack == NULL) // 检查内存分配是否成功
	{
		fprintf(stderr, "Error: Memory allocation failed for stack struct.\n");
		exit(EXIT_FAILURE); // 分配失败，终止程序
	}
	// 2. 为栈的 storage 数组分配内存
	stack->storage = (int *)malloc(capacity * sizeof(int));
	if (stack->storage == NULL) // 检查内存分配是否成功
	{
		fprintf(stderr, "Error: Memory allocation failed for stack storage.\n");
		free(stack); // 如果 storage 分配失败，也要释放之前分配的 struct 内存
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < capacity)
	{
		stack->storage[i] = 0;
		i++;
	}
	// 3. 初始化栈的成员
	stack->top = -1;            // 初始时，栈是空的，top 指向 -1
	stack->capacity = capacity; // 设置栈的容量
	stack->stack_size = 0;      // 栈的大小为 0
	return (stack);             // 返回新初始化的栈的指针
}
