/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	add_node(t_stack *a, int value);
static long	ft_atol(const char *str, bool *error);
static void	check_duplicates(t_stack *a);

void	parse_and_fill_a(int argc, char **argv, t_stack *a)
{
	int		i;
	bool	error;

	i = argc - 1;
	error = false;
	while (i > 0)
	{
		add_node(a, ft_atol(argv[i], &error));
		if (error)
		{
			write(2, "Error\n", 6);
			free_stack(a);
			exit(EXIT_FAILURE);
		}
		i--;
	}
	check_duplicates(a);
}

static void	add_node(t_stack *a, int value)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->value = value;
	new_node->rank = -1;
	if (a->top == NULL)
	{
		new_node->next = new_node;
		new_node->prev = new_node;
		a->top = new_node;
	}
	else
	{
		new_node->next = a->top;
		new_node->prev = a->top->prev;
		a->top->prev->next = new_node;
		a->top->prev = new_node;
		a->top = new_node;
	}
	a->size++;
}

static long	ft_atol(const char *str, bool *error)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		*error = true;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			*error = true;
		res = res * 10 + (str[i] - '0');
		i++;
	}
	res *= sign;
	if (res > INT_MAX || res < INT_MIN)
		*error = true;
	return (res);
}

static void	check_duplicates(t_stack *a)
{
	t_node	*current;
	t_node	*runner;
	int		i;
	int		j;

	if (!a || !a->top)
		return ;
	current = a->top;
	i = 0;
	while (i < a->size)
	{
		runner = current->next;
		j = i + 1;
		while (j < a->size)
		{
			if (current->value == runner->value)
			{
				write(2, "Error\n", 6);
				free_stack(a);
				exit(EXIT_FAILURE);
			}
			runner = runner->next;
			j++;
		}
		current = current->next;
		i++;
	}
}
