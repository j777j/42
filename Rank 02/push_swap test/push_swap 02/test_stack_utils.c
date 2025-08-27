/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_sorted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:45:07 by juwang            #+#    #+#             */
/*   Updated: 2025/07/02 17:49:53 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// file: test_is_sorted.c (你可以把这个文件放在项目根目录)

#include "includes/operations.h" // 包含我们的头文件，它有 t_stack 定义和 is_sorted 声明
#include <stdio.h>               // 用于 printf 打印输出
#include <stdlib.h>              // 用于 malloc 和 free

// 这是一个临时的辅助函数，用于初始化一个栈进行测试
// 注意：这只是为了测试方便，不是最终项目的初始化方式
void	init_test_stack(t_stack *stack, int *values, int count)
{
	int	i;

	stack->capacity = count;
	stack->storage = (int *)malloc(count * sizeof(int)); // 分配数组内存
	if (stack->storage == NULL)
	{
		fprintf(stderr, "Test Error: Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	stack->top = -1; // 初始化为空栈
	i = 0;
	while (i < count)
	{
		stack->storage[i] = values[i];
		stack->top = i;
		stack->stack_size = i + 1;
		i++;
	}
}

// 这是一个临时的辅助函数，用于打印栈的内容 (方便调试)
void	print_test_stack(t_stack *stack, const char *name)
{
	int	i;

	printf("Stack %s (%d/%d): [", name, stack->stack_size, stack->capacity);
	if (stack->stack_size == 0)
	{
		printf("]\n");
		return ;
	}
	i = 0;
	while (i < stack->stack_size)
	{
		printf("%d", stack->storage[i]);
		if (i < stack->stack_size - 1)
			printf(", ");
		i++;
	}
	printf("]\n");
}

int	main(void)
{
	t_stack	test_stack;

	int values1[] = {1, 2, 3, 4, 5}; // 有序的栈
	int values2[] = {5, 4, 3, 2, 1}; // 逆序的栈
	int values3[] = {1, 3, 2, 4, 5}; // 部分乱序的栈
	int values4[] = {42};            // 单个元素的栈
										// 空栈 (注意：C99/C11 允许零长度数组字面量，但通常用 count=0 模拟)
	printf("--- Testing is_sorted function ---\n");
	// 测试 1：有序的栈
	init_test_stack(&test_stack, values1, 5);
	print_test_stack(&test_stack, "Test 1");
	if (is_sorted(&test_stack))
		printf("Test 1 Result: Sorted (Correct)\n");
	else
		printf("Test 1 Result: Not Sorted (Error)\n");
	free(test_stack.storage); // 释放内存
	// 测试 2：逆序的栈
	init_test_stack(&test_stack, values2, 5);
	print_test_stack(&test_stack, "Test 2");
	if (is_sorted(&test_stack))
		printf("Test 2 Result: Sorted (Error)\n");
	else
		printf("Test 2 Result: Not Sorted (Correct)\n");
	free(test_stack.storage);
	// 测试 3：部分乱序的栈
	init_test_stack(&test_stack, values3, 5);
	print_test_stack(&test_stack, "Test 3");
	if (is_sorted(&test_stack))
		printf("Test 3 Result: Sorted (Error)\n");
	else
		printf("Test 3 Result: Not Sorted (Correct)\n");
	free(test_stack.storage);
	// 测试 4：单个元素的栈
	init_test_stack(&test_stack, values4, 1);
	print_test_stack(&test_stack, "Test 4");
	if (is_sorted(&test_stack))
		printf("Test 4 Result: Sorted (Correct)\n");
	else
		printf("Test 4 Result: Not Sorted (Error)\n");
	free(test_stack.storage);
	// 测试 5：空栈
	// 对于空栈，我们手动设置 stack_size 和 top
	test_stack.storage = NULL; // 没有分配内存
	test_stack.top = -1;
	test_stack.capacity = 0;
	test_stack.stack_size = 0;
	print_test_stack(&test_stack, "Test 5");
	if (is_sorted(&test_stack))
		printf("Test 5 Result: Sorted (Correct)\n");
	else
		printf("Test 5 Result: Not Sorted (Error)\n");
	// 不需要 free(test_stack.storage)，因为没有 malloc
	printf("--- Testing finished ---\n");
	return (0);
}
