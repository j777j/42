/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sort_three(t_stack *a)
{
	int	r1;
	int	r2;
	int	r3;

	if (is_sorted(a))
		return ;
	r1 = a->top->rank;
	r2 = a->top->next->rank;
	r3 = a->top->next->next->rank;
	if (r1 > r2 && r2 < r3 && r1 < r3)
		op_sa(a, true);
	else if (r1 > r2 && r2 > r3)
	{
		op_sa(a, true);
		op_rra(a, true);
	}
	else if (r1 > r2 && r2 < r3 && r1 > r3)
		op_ra(a, true);
	else if (r1 < r2 && r2 > r3 && r1 < r3)
	{
		op_sa(a, true);
		op_ra(a, true);
	}
	else
		op_rra(a, true);
}
