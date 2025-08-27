/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

/* --- Core Data Structures --- */

typedef struct s_node
{
	int				value;
	int				rank;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct s_stack
{
	t_node	*top;
	int		size;
}			t_stack;

typedef struct s_move
{
	int	ra;
	int	rb;
	int	rra;
	int	rrb;
	int	cost;
}	t_move;

/* --- Initialization & Parsing --- */
void	init_stacks(t_stack **a, t_stack **b);
void	parse_and_fill_a(int argc, char **argv, t_stack *a);
void	free_stack(t_stack *stack);

/* --- Ranking --- */
void	assign_ranks(t_stack *a);

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

/* --- Sorting Algorithm --- */
void	run_algorithm(t_stack *a, t_stack *b);
void	partition_to_b(t_stack *a, t_stack *b);
void	merge_to_a(t_stack *a, t_stack *b);
void	sort_three(t_stack *a);
void	final_alignment(t_stack *a);

/* --- Utils --- */
bool	is_sorted(t_stack *stack);
int		get_min_rank_pos(t_stack *stack);

#endif
