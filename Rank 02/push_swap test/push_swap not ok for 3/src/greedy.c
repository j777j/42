/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:39:33 by juwang            #+#    #+#             */
/*   Updated: 2025/07/06 10:30:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
 * get_target_pos_a: Finds the best position in stack A for a value from stack B.
 * The logic is to find the smallest number in A that is larger than b_val.
 * If no such number exists, it means b_val is the largest value, so it should
 * be placed right after the current maximum value in A (which is equivalent
 * to the position of the minimum value in a circularly sorted stack).
 */
int	get_target_pos_a(t_stack *a, int b_val)
{
	int	i;
	int	target_pos;
	int	closest_larger_val;

	i = 0;
	target_pos = -1;
	closest_larger_val = INT_MAX;
	// Find the smallest number in A that is strictly greater than b_val
	while (i < a->stack_size)
	{
		if (a->storage[i] > b_val && a->storage[i] < closest_larger_val)
		{
			closest_larger_val = a->storage[i];
			target_pos = i;
		}
		i++;
	}
	// If no such number was found, b_val is the new max.
	// The target position is the position of the minimum value in A.
	if (target_pos == -1)
	{
		return (find_min_value_pos(a));
	}
	return (target_pos);
}

/*
 * get_cheapest_cost: Calculates the minimum number of moves to get an element
 * from B to its target position in A.
 */
static int	get_cheapest_cost(t_stack *a, t_stack *b, int a_pos, int b_pos)
{
	int	ra_moves;
	int	rra_moves;
	int	rb_moves;
	int	rrb_moves;
	int	cost;

	ra_moves = a->top - a_pos;
	rra_moves = a_pos + 1;
	rb_moves = b->top - b_pos;
	rrb_moves = b_pos + 1;
	cost = (ra_moves > rb_moves ? ra_moves : rb_moves);
	if ((rra_moves > rrb_moves ? rra_moves : rrb_moves) < cost)
		cost = (rra_moves > rrb_moves ? rra_moves : rrb_moves);
	if ((ra_moves + rrb_moves) < cost)
		cost = ra_moves + rrb_moves;
	if ((rra_moves + rb_moves) < cost)
		cost = rra_moves + rb_moves;
	return (cost);
}

/*
 * find_best_move: Iterates through stack B to find the element that
 * can be moved to stack A with the minimum cost.
 */
void	find_best_move(t_stack *a, t_stack *b, int *a_pos, int *b_pos)
{
	int	current_b_pos;
	int	current_a_pos;
	int	cost;
	int	min_cost;

	current_b_pos = 0;
	min_cost = INT_MAX;
	while (current_b_pos < b->stack_size)
	{
		current_a_pos = get_target_pos_a(a, b->storage[current_b_pos]);
		cost = get_cheapest_cost(a, b, current_a_pos, current_b_pos);
		if (cost < min_cost)
		{
			min_cost = cost;
			*a_pos = current_a_pos;
			*b_pos = current_b_pos;
		}
		current_b_pos++;
	}
}