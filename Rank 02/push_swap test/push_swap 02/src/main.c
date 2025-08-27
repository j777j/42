/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:43:46 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 07:44:07 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
 * main: 程序的主入口点
 *
 * 功能:
 * 1. 检查是否有足够的命令行参数。
 * 2. 调用解析和验证函数来处理输入。
 * 3. 初始化 A 栈和 B 栈。
 * 4. 将处理好的数字填充到 A 栈。
 * 5. (未来在这里调用排序算法)。
 * 6. 释放所有分配的内存并干净地退出。
 */
int	main(int argc, char **argv)
{
	t_stack	*a_stack;
	t_stack	*b_stack;
	int		*parsed_nums;
	int		num_count;

	// 1. 如果没有输入数字 (只有程序名)，则静默退出
	if (argc < 2)
	{
		return (EXIT_SUCCESS);
	}
	// 2. 解析和验证输入
	parsed_nums = parse_and_validate_input(argc, argv, &num_count);
	// 3. 初始化 A 和 B 栈，容量为有效数字的数量
	a_stack = init_stack(num_count);
	b_stack = init_stack(num_count);
	// 4. 将数字填充到 A 栈
	fill_stack_a(a_stack, parsed_nums, num_count);
	// 5. 对 A 栈中的数字进行标准化(评级)
	simplify_numbers(a_stack);
	// 6. 运行主排序算法
	run_algorithm(a_stack, b_stack);
	// 7. 释放所有内存
	free_stacks(a_stack, b_stack);
	return (EXIT_SUCCESS);
}
