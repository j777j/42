/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	run_algorithm(t_stack *a, t_stack *b)
{
	if (a->size <= 1)
		return ;
	if (a->size == 2)
	{
		if (a->top->rank > a->top->next->rank)
			op_sa(a, true);
	}
	else if (a->size == 3)
		sort_three(a);
	else
	{
		partition_to_b(a, b);
		sort_three(a);
		merge_to_a(a, b);
		final_alignment(a);
	}
}
