/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:38:28 by juwang            #+#    #+#             */
/*   Updated: 2025/07/08 17:47:51 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sort_3_numbers(t_stack *a)
{
	int	top;
	int	mid;
	int	bot;

	top = a->storage[a->top];
	mid = a->storage[a->top - 1];
	bot = a->storage[a->top - 2];
	if (is_sorted(a))
		return ;
	// 3 2 1 -> sa, rra
	if (top > mid && mid > bot)
	{
		op_sa(a, true);
		op_rra(a, true);
	}
	// 2 1 3 -> sa
	else if (top > mid && mid < bot && top < bot)
		op_sa(a, true);
	// 3 1 2 -> ra
	else if (top > mid && mid < bot && top > bot)
		op_ra(a, true);
	// 1 3 2 -> sa, ra
	else if (top < mid && mid > bot && top < bot)
	{
		op_sa(a, true);
		op_ra(a, true);
	}
	// 2 3 1 -> rra
	else if (top < mid && mid > bot && top > bot)
		op_rra(a, true);
}

void	sort_5_numbers(t_stack *a, t_stack *b)
{
	int	min_pos;
	int	ra_cost;
	int	rra_cost;

	while (a->stack_size > 3)
	{
		min_pos = find_min_value_pos(a);
		ra_cost = a->top - min_pos;
		rra_cost = min_pos + 1;
		if (ra_cost < rra_cost)
		{
			while (ra_cost > 0)
			{
				op_ra(a, true);
				ra_cost--;
			}
		}
		else
		{
			while (rra_cost > 0)
			{
				op_rra(a, true);
				rra_cost--;
			}
		}
		op_pb(a, b, true);
	}
	sort_3_numbers(a);
	while (b->stack_size > 0)
		op_pa(a, b, true);
}
