/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:38:04 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 12:07:26 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
 * run_algorithm: 排序算法的总指挥
 *
 * 最终修正:
 * 将 sort_5_numbers 的适用范围扩大到所有数量较少的输入 (例如 <= 10)。
 * 这避免了在处理少量数字时，错误地调用为大量数字设计的、
 * 复杂且低效的 general_sort 算法。
 */
void	run_algorithm(t_stack *a, t_stack *b)
{
	int	size;

	size = a->stack_size;
	if (is_sorted(a) || size <= 1)
		return ;
	if (size == 2)
		op_sa(a, true);
	else if (size == 3)
		sort_3_numbers(a);
	else if (size <= 5) // 關鍵修正：將 10 改回 5
		sort_5_numbers(a, b);
	else
	{
		// 只有在数字真正多的时候，才调用重量级的通用算法
		general_sort(a, b);
	}
}
