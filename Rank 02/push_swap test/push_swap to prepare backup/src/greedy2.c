/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/15 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	execute_best_move(t_stack *a, t_stack *b, t_move *best_move)
{
	if (best_move->type == RR)
		execute_rr(a, b, best_move->ra, best_move->rb);
	else if (best_move->type == RRR)
		execute_rrr(a, b, best_move->rra, best_move->rrb);
	else if (best_move->type == RA_RRB)
	{
		execute_ra(a, best_move->ra);
		execute_rrb(b, best_move->rrb);
	}
	else
	{
		execute_rra(a, best_move->rra);
		execute_rb(b, best_move->rb);
	}
}

void	push_all_to_a_from_b_sorted(t_stack *a, t_stack *b)
{
	t_move	best_move;

	while (b->stack_size > 0)
	{
		find_best_move(a, b, &best_move);
		execute_best_move(a, b, &best_move);
		op_pa(a, b, true);
	}
}
