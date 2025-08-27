/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:35:56 by juwang            #+#    #+#             */
/*   Updated: 2025/07/16 17:57:05 by juwang           ###   ########.fr       */
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
	int			*storage;
	int			top;
	int			stack_size;
	int			capacity;
}				t_stack;

typedef enum e_move_type
{
	RR,
	RRR,
	RA_RRB,
	RRA_RB
}				t_move_type;

typedef struct s_move
{
	int			a_pos;
	int			b_pos;
	int			ra;
	int			rb;
	int			rra;
	int			rrb;
	int			cost;
	t_move_type	type;
}				t_move;

typedef struct s_cost
{
	int			ra;
	int			rb;
	int			rra;
	int			rrb;
}				t_cost;

/* --- Setup & Parsing --- */
t_stack			*init_stack(int capacity);
void			free_stacks(t_stack *a, t_stack *b);
int				*parse_and_validate_input(int argc, char **argv, int *count);
void			fill_stack_a(t_stack *a, int *nums, int count);
void			simplify_numbers(t_stack *a_stack);
int				ft_atoi_checked(const char *str, bool *error);
int				count_words(const char *str);
void			check_duplicates(int *nums, int count);

/* --- Operations --- */
void			op_sa(t_stack *a, bool print);
void			op_sb(t_stack *b, bool print);
void			op_ss(t_stack *a, t_stack *b, bool print);
void			op_pa(t_stack *a, t_stack *b, bool print);
void			op_pb(t_stack *a, t_stack *b, bool print);
void			op_ra(t_stack *a, bool print);
void			op_rb(t_stack *b, bool print);
void			op_rr(t_stack *a, t_stack *b, bool print);
void			op_rra(t_stack *a, bool print);
void			op_rrb(t_stack *b, bool print);
void			op_rrr(t_stack *a, t_stack *b, bool print);

/* --- Sorting Algorithms --- */
void			run_algorithm(t_stack *a, t_stack *b);
void			general_sort(t_stack *a, t_stack *b);
void			partition_a_to_b(t_stack *a, t_stack *b);
void			push_all_to_b_by_chunks(t_stack *a, t_stack *b);
void			push_all_to_a_from_b_sorted(t_stack *a, t_stack *b);
void			sort_3_numbers(t_stack *a);
void			sort_5_numbers(t_stack *a, t_stack *b);
void			final_alignment(t_stack *a);
void			find_best_move(t_stack *a, t_stack *b, t_move *best_move);
void			execute_best_move(t_stack *a, t_stack *b, t_move *best_move);
void			calculate_moves(t_stack *a, t_stack *b, t_move *moves);
int				get_target_pos_a(t_stack *a, int b_val);

/* --- Execution --- */
void			execute_ra(t_stack *a, int count);
void			execute_rb(t_stack *b, int count);
void			execute_rr(t_stack *a, t_stack *b, int ra_count, int rb_count);
void			execute_rra(t_stack *a, int count);
void			execute_rrb(t_stack *b, int count);
void			execute_rrr(t_stack *a, t_stack *b, int rra_count,
					int rrb_count);

/* --- Utils --- */
bool			is_sorted(t_stack *stack);
int				find_max_value(t_stack *stack);
int				find_value_pos(t_stack *stack, int value);
int				find_min_value_pos(t_stack *stack);
int				find_max_value_pos(t_stack *stack);
int				get_median(t_stack *stack, int size);
int				get_sub_median(t_stack *stack, int pivot, int size);

#endif
