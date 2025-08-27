/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:38:43 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 12:27:51 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdio.h> // 确保包含了 printf

/*
 * general_sort: 处理大量数字的通用排序算法总指挥
 * (带有详细的调试打印信息)
 */
void	general_sort(t_stack *a, t_stack *b)
{
	int	a_pos;
	int	b_pos;

	push_all_except_three(a, b);
	sort_3_numbers(a);
	while (b->stack_size > 0)
	{
		// printf("\n--- Greedy Loop Start (B size: %d) ---\n", b->stack_size);
		// print_stack(a, "A");
		// print_stack(b, "B");
		find_best_move(a, b, &a_pos, &b_pos);
		// printf("--- Executing Best Move ---\n");
		execute_best_move(a, b, a_pos, b_pos);
		op_pa(a, b, true);
	}
	final_alignment(a);
}
