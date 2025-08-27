/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_operations_sa.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:27:44 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 14:27:45 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// file: test_operations_sa.c

#include "includes/operations.h" // 包含头文件，它有 t_stack 定义和 op_sa 声明
#include <stdio.h>               // 用于 printf 打印输出
#include <stdlib.h>              // 用于 malloc 和 free

// --- 辅助测试函数 (和test_is_sorted.c 中的类似) ---
// 临时的栈初始化函数，只用于测试
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

// 临时的栈内容打印函数，方便调试
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
// --- 辅助测试函数结束 ---

int	main(void)
{
	t_stack	stack_a;

	int values1[] = {1, 2, 3}; // 至少有2个元素
	int values2[] = {10, 20};  // 刚好2个元素
	int values3[] = {42};      // 只有1个元素
	// int     values4[] = {};     // 空栈，手动设置
	printf("--- Testing op_sa function ---\n");
	// Test Case 1: 栈A有多个元素 (1, 2, 3) -> 交换后应为 (1, 3, 2) (因为交换的是顶部2个)
	printf("\nTest 1: Stack with multiple elements (1, 2, 3)\n");
	init_test_stack(&stack_a, values1, 3);
	print_test_stack(&stack_a, "A - Before op_sa");
	op_sa(&stack_a, true); // 执行 op_sa 并打印指令
	print_test_stack(&stack_a, "A - After op_sa");
	free(stack_a.storage); // 释放内存
	// Test Case 2: 栈A只有两个元素 (10, 20) -> 交换后应为 (20, 10)
	printf("\nTest 2: Stack with exactly two elements (10, 20)\n");
	init_test_stack(&stack_a, values2, 2);
	print_test_stack(&stack_a, "A - Before op_sa");
	op_sa(&stack_a, true); // 执行 op_sa 并打印指令
	print_test_stack(&stack_a, "A - After op_sa");
	free(stack_a.storage);
	// Test Case 3: 栈A只有一个元素 (42) -> 不应有任何操作
	printf("\nTest 3: Stack with only one element (42)\n");
	init_test_stack(&stack_a, values3, 1);
	print_test_stack(&stack_a, "A - Before op_sa");
	op_sa(&stack_a, true); // 执行 op_sa 并打印指令
	print_test_stack(&stack_a, "A - After op_sa (should be unchanged)");
	free(stack_a.storage);
	// Test Case 4: 栈A为空 -> 不应有任何操作
	printf("\nTest 4: Empty Stack\n");
	// 手动设置空栈
	stack_a.storage = NULL;
	stack_a.top = -1;
	stack_a.capacity = 0;
	stack_a.stack_size = 0;
	print_test_stack(&stack_a, "A - Before op_sa");
	op_sa(&stack_a, true); // 执行 op_sa 并打印指令
	print_test_stack(&stack_a, "A - After op_sa (should be unchanged)");
	// 空栈无需 free(storage) 因为没有 malloc
	printf("\n--- All op_sa tests finished ---\n");
	return (0);
}
