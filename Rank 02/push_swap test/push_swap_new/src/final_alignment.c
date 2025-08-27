/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_alignment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	final_alignment(t_stack *a)
{
	int	min_rank_pos;
	int	size;

	min_rank_pos = get_min_rank_pos(a);
	size = a->size;
	if (min_rank_pos > 0)
	{
		if (min_rank_pos <= size / 2)
		{
			while (min_rank_pos-- > 0)
				op_ra(a, true);
		}
		else
		{
			while (min_rank_pos++ < size)
				op_rra(a, true);
		}
	}
}
