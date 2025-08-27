/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:41:40 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 06:12:15 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

// 引入标准的C库，这些在各个 .c 文件中都会用到
# include <limits.h>  // 用于 INT_MIN, INT_MAX
# include <stdbool.h> // 用于 bool 类型
# include <stdio.h>   // 用于 fprintf, printf (调试用)
# include <stdlib.h>  // 用于 malloc, free, exit
# include <unistd.h>  // 可能用于 write

// --- 核心数据结构定义 (在 includes/push_swap.h 中，这里只是确保包含) ---
# include "push_swap.h"

// --- 栈初始化与释放原型 (在 src/stack_init_free.c, 确保它们在 main.c 中可用) ---
// init_stack_arr: 初始化栈，返回一个指向 t_stack 的指针
t_stack	*init_stack_arr(int capacity);
// free_stacks_arr: 释放 A 栈和 B 栈的所有内存 (包括 storage 数组和 t_stack 结构体本身)
void	free_stacks_arr(t_stack *a, t_stack *b);

// --- 通用栈辅助函数原型 (在 src/stack_utils.c) ---
bool	is_empty(t_stack *stack);
bool	is_sorted(t_stack *stack);
int		max_val_in_stack(t_stack *stack);

// --- 通用栈操作辅助函数原型 (在 src/stack_operations_helper.c) ---
int		pop_value(t_stack *stack);
void	push_value(t_stack *stack, int value);

// --- Push Swap 基本操作原型 (每个操作通常有自己的 .c 文件) ---
// 交换操作
void	op_sa(t_stack *stack, bool print_op);
void	op_sb(t_stack *stack, bool print_op);
void	op_ss(t_stack *a, t_stack *b, bool print_op);

// 推入操作
void	op_pa(t_stack *a, t_stack *b, bool print_op);
void	op_pb(t_stack *a, t_stack *b, bool print_op);

// 旋转操作
void	op_ra(t_stack *stack, bool print_op);
void	op_rb(t_stack *stack, bool print_op);
void	op_rr(t_stack *a, t_stack *b, bool print_op);

// 反向旋转操作
void	op_rra(t_stack *stack, bool print_op);
void	op_rrb(t_stack *stack, bool print_op);
void	op_rrr(t_stack *a, t_stack *b, bool print_op);

// --- 输入解析和栈填充原型 (在 src/input_parser.c) ---
int		*parse_input(int argc, char **argv, t_stack *a_ref);
void	fill_a(t_stack *a, int *nums, int count);

// --- 数字索引化/等级化原型 (在 src/ranking.c) ---
void	insertion_sort(int *arr, int size);
int		*gen_sorted_arr(t_stack *stack);
void	simplify_numbers(t_stack *stack, int *sorted_arr);

// --- 小数字量排序原型 (在 src/special_cases.c) ---
void	sort_3_numbers(t_stack *a);
void	sort_5_numbers(t_stack *a, t_stack *b);
void	rotate_to_top(t_stack *stack, int index, char print_op_char);

// --- 算法核心辅助函数原型 (在 src/algorithm_utils.c) ---
int		find_value_pos(t_stack *stack, int value);
int		get_target_pos_a(t_stack *a_stack, int b_val);
int		calculate_cost(t_stack *a_stack, t_stack *b_stack, int b_pos,
			int a_target_pos);
// void	execute_best_move(t_stack *a_stack, t_stack *b_stack, int b_val_pos,
// 			int a_target_pos);

// --- 算法核心主函数原型 (在 src/algorithm_main.c) ---
void	run_xiaoyou_algorithm(t_stack *a_stack, t_stack *b_stack);

void	print_test_stack(t_stack *stack, const char *name);
#endif // OPERATIONS_H
