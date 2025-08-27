/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:38:28 by juwang            #+#    #+#             */
/*   Updated: 2025/07/16 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sort_3_numbers(t_stack *a)
{
	int	max_val;

	if (is_sorted(a))
		return ;
	max_val = find_max_value(a);
	if (a->storage[a->top] == max_val)
		op_ra(a, true);
	else if (a->storage[a->top - 1] == max_val)
		op_rra(a, true);
	if (a->storage[a->top] > a->storage[a->top - 1])
		op_sa(a, true);
}

static void	push_val_to_b(t_stack *a, t_stack *b, int val)
{
	int	pos;
	int	ra_cost;
	int	rra_cost;

	pos = find_value_pos(a, val);
	ra_cost = a->stack_size - 1 - pos;
	rra_cost = pos + 1;
	if (ra_cost <= rra_cost)
	{
		while (ra_cost-- > 0)
			op_ra(a, true);
	}
	else
	{
		while (rra_cost-- > 0)
			op_rra(a, true);
	}
	op_pb(a, b, true);
}

void	sort_5_numbers(t_stack *a, t_stack *b)
{
	push_val_to_b(a, b, 0);
	push_val_to_b(a, b, 1);
	sort_3_numbers(a);
	op_pa(a, b, true);
	op_pa(a, b, true);
}
