/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	init_stacks(t_stack **a, t_stack **b)
{
	*a = (t_stack *)malloc(sizeof(t_stack));
	*b = (t_stack *)malloc(sizeof(t_stack));
	if (!*a || !*b)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	(*a)->top = NULL;
	(*a)->size = 0;
	(*b)->top = NULL;
	(*b)->size = 0;
}

void	free_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*next;

	if (!stack || !stack->top)
	{
		free(stack);
		return ;
	}
	current = stack->top;
	stack->top->prev->next = NULL;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(stack);
}
