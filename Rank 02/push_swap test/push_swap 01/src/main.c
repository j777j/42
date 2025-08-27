/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:43:46 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 19:10:27 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h" // 包含所有我们需要的函数声明和数据结构定义

// main 函数：程序的入口点
// argc - 命令行参数的数量 (argument count)
// argv - 命令行参数的字符串数组 (argument vector)
int	main(int argc, char **argv)
{
	int	k;

	t_stack *a_stack;     // 声明 A 栈变量
	t_stack *b_stack;     // 声明 B 栈变量
	int *input_numbers;   // 用于存储从命令行解析出来的数字
	int *temp_sorted_arr; // 新增变量，用于调试
	// 1. 检查命令行参数数量
	// 如果没有提供数字 (argc < 2，因为 argv[0] 是程序名)
	if (argc < 2)
	{
		// 按照 Push Swap 挑战的要求，没有参数时通常静默退出
		return (EXIT_SUCCESS); // 成功退出，返回 0
	}
	// 2. 初始化栈的容量 (所有数字都在 A 栈中，B 栈最初为空，但总容量与 A 栈相同)
	// argc - 1 是因为实际的数字是除了程序名之外的参数
	a_stack = init_stack_arr(argc - 1); // 初始化 A 栈，为其 storage 分配内存
	b_stack = init_stack_arr(argc - 1); // 初始化 B 栈，为其 storage 分配内存
	// 3. 解析命令行参数并填充 A 栈
	// parse_input 会返回一个动态分配的数组 (input_numbers)
	// fill_a 会将这些数字填充到 a_stack 中，并释放 input_numbers 数组
	input_numbers = parse_input(argc, argv, a_stack); // 解析输入，并进行错误检查
	fill_a(a_stack, input_numbers, argc - 1);
	// --- 修正点：在调用 simplify_numbers 之前进行调试打印 ---
	printf("DEBUG: Before simplify_numbers. A_stack contents (original numbers):\n");
	print_test_stack(a_stack, "A_ORIGINAL_NUMBERS");
	temp_sorted_arr = gen_sorted_arr(a_stack);
	printf("DEBUG: After gen_sorted_arr. Sorted array contents:\n");
	// 打印 temp_sorted_arr 的内容 (这里需要手动遍历打印，因为 print_test_stack 接受 t_stack*)
	k = 0;
	printf("Sorted Array: [");
	while (k < a_stack->stack_size)
	{
		printf("%d", temp_sorted_arr[k]);
		if (k < a_stack->stack_size - 1)
			printf(", ");
		k++;
	}
	printf("]\n");
	simplify_numbers(a_stack, temp_sorted_arr); // 传递 temp_sorted_arr
	printf("DEBUG: After simplify_numbers. A_stack contents (ranks):\n");
	print_test_stack(a_stack, "A_RANKS");
	// --- 修正结束 ---
	// 填充 A 栈
	// 4. 检查 A 栈是否已经排序 (初始状态)
	if (is_sorted(a_stack))
	{
		// 如果 A 栈已经排序，则无需任何操作，直接清理内存并退出
		free_stacks_arr(a_stack, b_stack); // 释放栈的内存
		return (EXIT_SUCCESS);
	}
	// 5. 调用核心排序算法 (这是我们“小优”算法的主体，目前只是占位符)
	// 之后，我们会在这里调用我们的“混合优化 Push Swap”算法
	run_xiaoyou_algorithm(a_stack, b_stack);
	// 例如：run_xiaoyou_algorithm(a_stack, b_stack);
	// 6. 清理内存
	free_stacks_arr(a_stack, b_stack); // 释放 A 栈和 B 栈的 storage 内存
	return (EXIT_SUCCESS);             // 程序成功完成，返回 0
}
