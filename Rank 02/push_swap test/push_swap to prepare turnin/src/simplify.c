/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:37:36 by juwang            #+#    #+#             */
/*   Updated: 2025/07/16 23:21:37 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	insertion_sort(int *arr, int size)
{
	int	i;
	int	j;
	int	key;

	i = 1;
	while (i < size)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
		i++;
	}
}

static void	copy_stack_to_array(t_stack *stack, int *arr)
{
	int	i;

	i = 0;
	while (i < stack->stack_size)
	{
		arr[i] = stack->storage[i];
		i++;
	}
}

static void	map_values_to_indices(t_stack *stack, int *sorted, int *temp)
{
	int	i;
	int	j;

	i = 0;
	while (i < stack->stack_size)
	{
		j = 0;
		while (j < stack->stack_size)
		{
			if (stack->storage[i] == sorted[j])
			{
				temp[i] = j;
				break ;
			}
			j++;
		}
		i++;
	}
}

static void	update_stack_storage(t_stack *stack, int *temp)
{
	int	i;

	i = 0;
	while (i < stack->stack_size)
	{
		stack->storage[i] = temp[i];
		i++;
	}
}

void	simplify_numbers(t_stack *a_stack)
{
	int	*sorted_arr;
	int	*temp_storage;

	sorted_arr = (int *)malloc(sizeof(int) * a_stack->stack_size);
	if (sorted_arr == NULL)
		exit(EXIT_FAILURE);
	copy_stack_to_array(a_stack, sorted_arr);
	insertion_sort(sorted_arr, a_stack->stack_size);
	temp_storage = (int *)malloc(sizeof(int) * a_stack->stack_size);
	if (temp_storage == NULL)
	{
		free(sorted_arr);
		exit(EXIT_FAILURE);
	}
	map_values_to_indices(a_stack, sorted_arr, temp_storage);
	update_stack_storage(a_stack, temp_storage);
	free(sorted_arr);
	free(temp_storage);
}
