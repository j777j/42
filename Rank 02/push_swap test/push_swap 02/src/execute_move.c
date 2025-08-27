/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 08:09:32 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 09:24:37 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	execute_rr(t_stack *a, t_stack *b, int ra_count, int rb_count)
{
	while (ra_count > 0 && rb_count > 0)
	{
		op_rr(a, b, true);
		ra_count--;
		rb_count--;
	}
	while (ra_count-- > 0)
		op_ra(a, true);
	while (rb_count-- > 0)
		op_rb(b, true);
}

static void	execute_rrr(t_stack *a, t_stack *b, int rra_count, int rrb_count)
{
	while (rra_count > 0 && rrb_count > 0)
	{
		op_rrr(a, b, true);
		rra_count--;
		rrb_count--;
	}
	while (rra_count-- > 0)
		op_rra(a, true);
	while (rrb_count-- > 0)
		op_rrb(b, true);
}

/*
 * execute_best_move: 根据成本最低的方案，执行一系列旋转操作
 *
 * 根本性修正:
 * 彻底纠正了所有成本和步数的计算，使其与操作的实际效果完全匹配。
 */
void	execute_best_move(t_stack *a, t_stack *b, int a_pos, int b_pos)
{
	int	ra_m;
	int	rra_m;
	int	rb_m;
	int	rrb_m;
	int	cost_rr;
	int	cost_rrr;
	int	cost_ra_rrb;
	int	cost_rra_rb;
	int	min_cost;

	ra_m = a_pos + 1;
	rra_m = a->top - a_pos;
	rb_m = b_pos + 1;
	rrb_m = b->top - b_pos;
	cost_rr = (ra_m > rb_m) ? ra_m : rb_m;
	cost_rrr = (rra_m > rrb_m) ? rra_m : rrb_m;
	cost_ra_rrb = ra_m + rrb_m;
	cost_rra_rb = rra_m + rb_m;
	min_cost = cost_rr;
	if (cost_rrr < min_cost)
		min_cost = cost_rrr;
	if (cost_ra_rrb < min_cost)
		min_cost = cost_ra_rrb;
	if (cost_rra_rb < min_cost)
		min_cost = cost_rra_rb;
	if (min_cost == cost_rr)
		execute_rr(a, b, ra_m, rb_m);
	else if (min_cost == cost_rrr)
		execute_rrr(a, b, rra_m, rrb_m);
	else if (min_cost == cost_ra_rrb)
	{
		while (ra_m-- > 0)
			op_ra(a, true);
		while (rrb_m-- > 0)
			op_rrb(b, true);
	}
	else
	{
		while (rra_m-- > 0)
			op_rra(a, true);
		while (rb_m-- > 0)
			op_rb(b, true);
	}
}
