/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:38:58 by juwang            #+#    #+#             */
/*   Updated: 2025/07/16 17:12:18 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
 * Pushes all elements from stack A to B using a chunking strategy.
 * It divides the numbers into chunks and pushes them to B in a way
 * that makes sorting them back to A more efficient.
 */
void	push_all_to_b_by_chunks(t_stack *a, t_stack *b)
{
	int	size;
	int	i;
	int	chunk_size;
	int	num_chunks;

	size = a->stack_size;
	if (size <= 100)
		num_chunks = 5;
	else
		num_chunks = 11;
	chunk_size = size / num_chunks;
	i = 0;
	while (a->stack_size > 0)
	{
		if (a->storage[a->top] <= i)
		{
			op_pb(a, b, true);
			i++;
			if (b->storage[b->top] < (i - chunk_size))
				op_rb(b, true);
		}
		else
			op_ra(a, true);
	}
}

/*
 * general_sort: Handles the sorting of large lists of numbers using
 * a median-based partitioning and greedy insertion strategy.
 *
 * 1. `partition_a_to_b`: Pushes elements from stack A to stack B in
 *    partitions based on medians, until 3 elements remain in A.
 * 2. `sort_3_numbers`: Sorts the three remaining elements in stack A.
 * 3. `push_all_to_a_from_b_sorted`: Greedily moves all elements from B
 *    back to A by calculating the cheapest move for each element.
 * 4. `final_alignment`: Rotates stack A to place the smallest element
 *    at the top, completing the sort.
 */
void	general_sort(t_stack *a, t_stack *b)
{
	partition_a_to_b(a, b);
	if (!is_sorted(a))
		sort_3_numbers(a);
	push_all_to_a_from_b_sorted(a, b);
	final_alignment(a);
}

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
	else if (size <= 5)
		sort_5_numbers(a, b);
	else
		general_sort(a, b);
}
