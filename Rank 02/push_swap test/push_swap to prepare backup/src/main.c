/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:36:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 09:36:18 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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
