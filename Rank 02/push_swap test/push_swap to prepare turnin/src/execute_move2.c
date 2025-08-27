/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_move2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/15 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	execute_rrr(t_stack *a, t_stack *b, int rra_count, int rrb_count)
{
	while (rra_count > 0 && rrb_count > 0)
	{
		op_rrr(a, b, true);
		rra_count--;
		rrb_count--;
	}
	execute_rra(a, rra_count);
	execute_rrb(b, rrb_count);
}
