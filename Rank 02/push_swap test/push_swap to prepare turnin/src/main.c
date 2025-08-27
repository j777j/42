/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:36:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/16 23:11:02 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	fill_stack_a(t_stack *a, int *nums, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		a->storage[count - 1 - i] = nums[i];
		a->stack_size++;
		i++;
	}
	a->top = count - 1;
	free(nums);
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

/*
 * final_alignment: Rotates stack A until the smallest element is at the top.
 * This is the final step to ensure the stack is perfectly sorted.
 */
void	final_alignment(t_stack *a)
{
	int	min_pos;
	int	ra_moves;
	int	rra_moves;

	min_pos = find_min_value_pos(a);
	ra_moves = a->top - min_pos;
	rra_moves = min_pos + 1;
	if (ra_moves < rra_moves)
	{
		while (ra_moves-- > 0)
			op_ra(a, true);
	}
	else
	{
		while (rra_moves-- > 0)
			op_rra(a, true);
	}
}

int	main(int argc, char **argv)
{
	t_stack	*a_stack;
	t_stack	*b_stack;
	int		*parsed_nums;
	int		num_count;

	if (argc < 2)
		return (EXIT_SUCCESS);
	parsed_nums = parse_and_validate_input(argc, argv, &num_count);
	a_stack = init_stack(num_count);
	b_stack = init_stack(num_count);
	fill_stack_a(a_stack, parsed_nums, num_count);
	simplify_numbers(a_stack);
	run_algorithm(a_stack, b_stack);
	free_stacks(a_stack, b_stack);
	return (EXIT_SUCCESS);
}
