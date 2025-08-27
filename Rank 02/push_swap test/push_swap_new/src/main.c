/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		return (0);
	init_stacks(&a, &b);
	parse_and_fill_a(argc, argv, a);
	assign_ranks(a);
	if (!is_sorted(a))
		run_algorithm(a, b);
	free_stack(a);
	free_stack(b);
	return (0);
}
