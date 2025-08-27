/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:37:36 by juwang            #+#    #+#             */
/*   Updated: 2025/07/06 14:00:00 by juwang           ###   ########.fr       */
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

/*
 * simplify_numbers: Replaces each number in the stack with its rank (index)
 *                   from a sorted version of the numbers. This is the final
 *                   and correct version of this crucial function.
 */
void	simplify_numbers(t_stack *a_stack)
{
	int	*sorted_arr;
	int	*temp_storage;
	int	i;
	int	j;

	// Create a temporary copy of the stack's storage to sort
	sorted_arr = (int *)malloc(sizeof(int) * a_stack->stack_size);
	if (sorted_arr == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < a_stack->stack_size)
	{
		sorted_arr[i] = a_stack->storage[i];
		i++;
	}
	insertion_sort(sorted_arr, a_stack->stack_size);

	// Create another temporary storage to hold the new simplified values
	temp_storage = (int *)malloc(sizeof(int) * a_stack->stack_size);
	if (temp_storage == NULL)
	{
		free(sorted_arr);
		exit(EXIT_FAILURE);
	}

	// For each element in the original stack, find its rank in the sorted array
	i = 0;
	while (i < a_stack->stack_size)
	{
		j = 0;
		while (j < a_stack->stack_size)
		{
			if (a_stack->storage[i] == sorted_arr[j])
			{
				temp_storage[i] = j;
				break;
			}
			j++;
		}
		i++;
	}

	// Copy the simplified values back into the stack's storage
	i = 0;
	while (i < a_stack->stack_size)
	{
		a_stack->storage[i] = temp_storage[i];
		i++;
	}

	free(sorted_arr);
	free(temp_storage);
}