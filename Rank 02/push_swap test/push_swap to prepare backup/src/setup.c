/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:37:03 by juwang            #+#    #+#             */
/*   Updated: 2025/07/15 17:50:41 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	fill_stack_a(t_stack *a, int *nums, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		a->storage[count - 1 - i] = nums[i];
		a->stack_size++;
		i++;
	}
	a->top = count - 1;
	free(nums);
}
