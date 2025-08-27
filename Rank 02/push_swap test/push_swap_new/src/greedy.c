/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	get_target_pos(t_stack *a, int rank)
{
	t_node	*current;
	int		pos;
	int		target_pos;
	int		closest_rank;

	current = a->top;
	pos = 0;
	target_pos = -1;
	closest_rank = INT_MAX;
	while (pos < a->size)
	{
		if (current->rank > rank && current->rank < closest_rank)
		{
			closest_rank = current->rank;
			target_pos = pos;
		}
		current = current->next;
		pos++;
	}
	if (target_pos == -1)
		return (get_min_rank_pos(a));
	return (target_pos);
}

static void	calculate_costs(t_stack *a, t_stack *b, t_move *moves)
{
	t_node	*b_node;
	int		pos_b;
	int		pos_a;
	int		i;
	int		cost_ra_rb;
	int		cost_rra_rrb;
	int		cost_ra_rrb;
	int		cost_rra_rb;

	b_node = b->top;
	i = 0;
	while (i < b->size)
	{
		pos_b = i;
		pos_a = get_target_pos(a, b_node->rank);
		cost_ra_rb = (pos_a > pos_b) ? pos_a : pos_b;
		cost_rra_rrb = ((a->size - pos_a) > (b->size - pos_b)) ? (a->size - pos_a) : (b->size - pos_b);
		cost_ra_rrb = pos_a + (b->size - pos_b);
		cost_rra_rb = (a->size - pos_a) + pos_b;
		if (cost_ra_rb <= cost_rra_rrb && cost_ra_rb <= cost_ra_rrb && cost_ra_rb <= cost_rra_rb)
		{
			moves[i].cost = cost_ra_rb;
			moves[i].ra = pos_a;
			moves[i].rb = pos_b;
			moves[i].rra = 0;
			moves[i].rrb = 0;
		}
		else if (cost_rra_rrb < cost_ra_rb && cost_rra_rrb <= cost_ra_rrb && cost_rra_rrb <= cost_rra_rb)
		{
			moves[i].cost = cost_rra_rrb;
			moves[i].ra = 0;
			moves[i].rb = 0;
			moves[i].rra = a->size - pos_a;
			moves[i].rrb = b->size - pos_b;
		}
		else if (cost_ra_rrb < cost_ra_rb && cost_ra_rrb < cost_rra_rrb && cost_ra_rrb <= cost_rra_rb)
		{
			moves[i].cost = cost_ra_rrb;
			moves[i].ra = pos_a;
			moves[i].rb = 0;
			moves[i].rra = 0;
			moves[i].rrb = b->size - pos_b;
		}
		else
		{
			moves[i].cost = cost_rra_rb;
			moves[i].ra = 0;
			moves[i].rb = pos_b;
			moves[i].rra = a->size - pos_a;
			moves[i].rrb = 0;
		}
		b_node = b_node->next;
		i++;
	}
}

static int	find_cheapest_move(t_stack *b, t_move *moves)
{
	int	i;
	int	cheapest_pos;
	int	min_cost;

	i = 0;
	cheapest_pos = 0;
	min_cost = moves[0].cost;
	while (i < b->size)
	{
		if (moves[i].cost < min_cost)
		{
			min_cost = moves[i].cost;
			cheapest_pos = i;
		}
		i++;
	}
	return (cheapest_pos);
}

static void	execute_moves(t_stack *a, t_stack *b, t_move move)
{
	while (move.ra > 0 && move.rb > 0)
	{
		op_rr(a, b, true);
		move.ra--;
		move.rb--;
	}
	while (move.rra > 0 && move.rrb > 0)
	{
		op_rrr(a, b, true);
		move.rra--;
		move.rrb--;
	}
	while (move.ra-- > 0)
		op_ra(a, true);
	while (move.rb-- > 0)
		op_rb(b, true);
	while (move.rra-- > 0)
		op_rra(a, true);
	while (move.rrb-- > 0)
		op_rrb(b, true);
	op_pa(a, b, true);
}

void	merge_to_a(t_stack *a, t_stack *b)
{
	t_move	*moves;
	int		cheapest_pos;

	while (b->size > 0)
	{
		moves = malloc(sizeof(t_move) * b->size);
		if (!moves)
			return ;
		calculate_costs(a, b, moves);
		cheapest_pos = find_cheapest_move(b, moves);
		execute_moves(a, b, moves[cheapest_pos]);
		free(moves);
	}
}
