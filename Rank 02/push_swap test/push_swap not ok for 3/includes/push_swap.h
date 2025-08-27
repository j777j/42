/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:35:56 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 10:03:18 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int	*storage;
	int	top;
	int	stack_size;
	int	capacity;
}		t_stack;

/* --- Setup & Parsing --- */
t_stack	*init_stack(int capacity);
void	free_stacks(t_stack *a, t_stack *b);
int		*parse_and_validate_input(int argc, char **argv, int *count);
void	fill_stack_a(t_stack *a, int *nums, int count);
void	simplify_numbers(t_stack *a_stack);

/* --- Operations --- */
void	op_sa(t_stack *a, bool print);
void	op_sb(t_stack *b, bool print);
void	op_ss(t_stack *a, t_stack *b, bool print);
void	op_pa(t_stack *a, t_stack *b, bool print);
void	op_pb(t_stack *a, t_stack *b, bool print);
void	op_ra(t_stack *a, bool print);
void	op_rb(t_stack *b, bool print);
void	op_rr(t_stack *a, t_stack *b, bool print);
void	op_rra(t_stack *a, bool print);
void	op_rrb(t_stack *b, bool print);
void	op_rrr(t_stack *a, t_stack *b, bool print);

/* --- Sorting Algorithms --- */
void	run_algorithm(t_stack *a, t_stack *b);
void	general_sort(t_stack *a, t_stack *b);
void	push_all_except_three(t_stack *a, t_stack *b);
void	final_alignment(t_stack *a);
void	sort_3_numbers(t_stack *a);
void	sort_5_numbers(t_stack *a, t_stack *b);

/* --- Greedy Algorithm --- */
int		get_target_pos_a(t_stack *a, int b_val);
void	find_best_move(t_stack *a, t_stack *b, int *a_pos, int *b_pos);
void	execute_best_move(t_stack *a, t_stack *b, int a_pos, int b_pos);

/* --- Utils --- */
bool	is_sorted(t_stack *stack);
int		find_max_value(t_stack *stack);
int		find_value_pos(t_stack *stack, int value);
int		find_min_value_pos(t_stack *stack);
int		is_sorted_int_array(int *nums, int count);

void	print_stack(t_stack *stack, const char *name);

#endif
