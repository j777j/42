/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:38:58 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 12:42:05 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	get_chunk_size(int total_size)
{
	if (total_size <= 100)
		return (20);
	if (total_size <= 500)
		return (40);
	return (100);
}

void	push_all_except_three(t_stack *a, t_stack *b)
{
	int	chunk_size;
	int	pushed_count;
	int	current_chunk;

	chunk_size = get_chunk_size(a->stack_size);
	pushed_count = 0;
	current_chunk = 1;
	while (a->stack_size > 3)
	{
		if (a->storage[a->top] <= pushed_count)
		{
			op_pb(a, b, true);
			pushed_count++;
			op_rb(b, true);
		}
		else if (a->storage[a->top] <= pushed_count + chunk_size)
		{
			op_pb(a, b, true);
			pushed_count++;
		}
		else
			op_ra(a, true);
		if (pushed_count >= chunk_size * current_chunk)
			current_chunk++;
	}
}