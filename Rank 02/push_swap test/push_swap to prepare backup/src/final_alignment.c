/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_alignment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:40:08 by juwang            #+#    #+#             */
/*   Updated: 2025/07/15 17:55:45 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
 * final_alignment: Rotates stack A until the smallest element is at the top.
 * This is the final step to ensure the stack is perfectly sorted.
 */
void	final_alignment(t_stack *a)
{
	int	min_pos;
	int	ra_moves;
	int	rra_moves;

	min_pos = find_min_value_pos(a);
	ra_moves = a->top - min_pos;
	rra_moves = min_pos + 1;
	if (ra_moves < rra_moves)
	{
		while (ra_moves-- > 0)
			op_ra(a, true);
	}
	else
	{
		while (rra_moves-- > 0)
			op_rra(a, true);
	}
}
