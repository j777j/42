/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:39:51 by juwang            #+#    #+#             */
/*   Updated: 2025/07/15 17:51:18 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	execute_ra(t_stack *a, int count)
{
	while (count-- > 0)
		op_ra(a, true);
}

void	execute_rb(t_stack *b, int count)
{
	while (count-- > 0)
		op_rb(b, true);
}

void	execute_rr(t_stack *a, t_stack *b, int ra_count, int rb_count)
{
	while (ra_count > 0 && rb_count > 0)
	{
		op_rr(a, b, true);
		ra_count--;
		rb_count--;
	}
	execute_ra(a, ra_count);
	execute_rb(b, rb_count);
}

void	execute_rra(t_stack *a, int count)
{
	while (count-- > 0)
		op_rra(a, true);
}

void	execute_rrb(t_stack *b, int count)
{
	while (count-- > 0)
		op_rrb(b, true);
}
