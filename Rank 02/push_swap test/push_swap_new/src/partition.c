/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	get_chunk_count(int size)
{
	if (size <= 100)
		return (3);
	if (size <= 500)
		return (7);
	return (11);
}

void	partition_to_b(t_stack *a, t_stack *b)
{
	int	num_chunks;
	int	chunk_size;
	int	pushed_count;
	int	i;
	int	threshold;
	int	total_size;

	total_size = a->size;
	num_chunks = get_chunk_count(total_size);
	chunk_size = total_size / num_chunks;
	pushed_count = 0;
	i = 1;
	while (a->size > 3)
	{
		threshold = chunk_size * i;
		if (i > num_chunks)
			threshold = total_size;
		while (pushed_count < threshold && a->size > 3)
		{
			if (a->top->rank < threshold)
			{
				op_pb(a, b, true);
				pushed_count++;
				if (b->top->rank < (threshold - chunk_size / 2))
				{
					if (b->size > 1)
						op_rb(b, true);
				}
			}
			else
				op_ra(a, true);
		}
		i++;
	}
}