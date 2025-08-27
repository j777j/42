/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:39:33 by juwang            #+#    #+#             */
/*   Updated: 2025/07/11 14:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	get_target_pos_a(t_stack *a, int b_val)
{
	int	i;
	int	target_pos;
	int	closest_larger_val;

	i = 0;
	target_pos = -1;
	closest_larger_val = INT_MAX;
	while (i < a->stack_size)
	{
		if (a->storage[i] > b_val && a->storage[i] < closest_larger_val)
		{
			closest_larger_val = a->storage[i];
			target_pos = i;
		}
		i++;
	}
	if (target_pos == -1)
		return (find_min_value_pos(a));
	return (target_pos);
}

static void	set_move_type(t_move *m, t_cost *c, int crr, int crrr)
{
	int	cost_ra_rrb;
	int	cost_rra_rb;

	cost_ra_rrb = c->ra + c->rrb;
	cost_rra_rb = c->rra + c->rb;
	m->cost = crr;
	m->type = RR;
	if (crrr < m->cost)
	{
		m->cost = crrr;
		m->type = RRR;
	}
	if (cost_ra_rrb < m->cost)
	{
		m->cost = cost_ra_rrb;
		m->type = RA_RRB;
	}
	if (cost_rra_rb < m->cost)
	{
		m->cost = cost_rra_rb;
		m->type = RRA_RB;
	}
}

static void	set_costs(t_move *m, t_cost *c)
{
	int	cost_rr;
	int	cost_rrr;

	cost_rr = c->ra;
	if (c->rb > c->ra)
		cost_rr = c->rb;
	cost_rrr = c->rra;
	if (c->rrb > c->rra)
		cost_rrr = c->rrb;
	set_move_type(m, c, cost_rr, cost_rrr);
}

void	calculate_moves(t_stack *a, t_stack *b, t_move *moves)
{
	t_cost	costs;

	costs.ra = a->stack_size - 1 - moves->a_pos;
	costs.rra = moves->a_pos + 1;
	costs.rb = b->stack_size - 1 - moves->b_pos;
	costs.rrb = moves->b_pos + 1;
	moves->ra = costs.ra;
	moves->rb = costs.rb;
	moves->rra = costs.rra;
	moves->rrb = costs.rrb;
	set_costs(moves, &costs);
}

void	find_best_move(t_stack *a, t_stack *b, t_move *best_move)
{
	int		current_b_pos;
	int		current_a_pos;
	t_move	current_move;

	current_b_pos = 0;
	best_move->cost = INT_MAX;
	while (current_b_pos < b->stack_size)
	{
		current_a_pos = get_target_pos_a(a, b->storage[current_b_pos]);
		current_move.a_pos = current_a_pos;
		current_move.b_pos = current_b_pos;
		calculate_moves(a, b, &current_move);
		if (current_move.cost < best_move->cost)
			*best_move = current_move;
		current_b_pos++;
	}
}
