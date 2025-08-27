/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/15 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	bubble_sort(int *arr, int n)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	get_median(t_stack *stack, int size)
{
	int	*temp_arr;
	int	median;
	int	i;

	if (stack == NULL || size == 0)
		return (0);
	temp_arr = (int *)malloc(sizeof(int) * size);
	if (!temp_arr)
		return (0);
	i = 0;
	while (i < size)
	{
		temp_arr[i] = stack->storage[stack->top - i];
		i++;
	}
	bubble_sort(temp_arr, size);
	median = temp_arr[size / 2];
	free(temp_arr);
	return (median);
}

static int	*create_sub_array(t_stack *st, int p, int sz, int *sub_cnt)
{
	int	*sub_arr;
	int	i;

	sub_arr = (int *)malloc(sizeof(int) * sz);
	if (!sub_arr)
		return (NULL);
	*sub_cnt = 0;
	i = 0;
	while (i < sz)
	{
		if (st->storage[st->top - i] < p)
		{
			sub_arr[*sub_cnt] = st->storage[st->top - i];
			(*sub_cnt)++;
		}
		i++;
	}
	return (sub_arr);
}

int	get_sub_median(t_stack *stack, int pivot, int size)
{
	int	*sub_arr;
	int	sub_count;
	int	median;

	if (stack == NULL || stack->stack_size == 0)
		return (0);
	sub_arr = create_sub_array(stack, pivot, size, &sub_count);
	if (!sub_arr)
		return (0);
	if (sub_count == 0)
	{
		free(sub_arr);
		return (pivot);
	}
	bubble_sort(sub_arr, sub_count);
	median = sub_arr[sub_count / 2];
	free(sub_arr);
	return (median);
}
