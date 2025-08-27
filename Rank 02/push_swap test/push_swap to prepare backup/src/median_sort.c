/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   median_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	partition_a_to_b(t_stack *a, t_stack *b)
{
	int	median_a;
	int	median_x;
	int	initial_size;
	int	i;

	while (a->stack_size > 3)
	{
		initial_size = a->stack_size;
		median_a = get_median(a, initial_size);
		median_x = get_sub_median(a, median_a, initial_size);
		i = 0;
		while (i < initial_size && a->stack_size > 3)
		{
			if (a->storage[a->top] < median_a)
			{
				op_pb(a, b, true);
				if (b->storage[b->top] < median_x)
					op_rb(b, true);
			}
			else
				op_ra(a, true);
			i++;
		}
	}
}
