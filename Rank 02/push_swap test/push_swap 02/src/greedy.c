/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:21:18 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 09:28:26 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
 * get_target_pos_a: 在 A 栈中为来自 B 栈的 b_val 找到最佳插入位置
 * (此函数已正确，保持不变)
 */
int	get_target_pos_a(t_stack *a, int b_val)
{
	int	target_pos;
	int	best_match_val;
	int	i;

	target_pos = -1;
	best_match_val = INT_MAX;
	i = 0;
	while (i < a->stack_size)
	{
		if (a->storage[i] > b_val && a->storage[i] < best_match_val)
		{
			best_match_val = a->storage[i];
			target_pos = i;
		}
		i++;
	}
	if (target_pos == -1)
	{
		target_pos = find_min_value_pos(a);
	}
	return (target_pos);
}

/*
 * get_cheapest_cost: 计算将 B 栈某个元素推入 A 栈所需的真正最小操作步数
 *
 * 修正:
 * 彻底纠正了 ra/rra/rb/rrb 的计算逻辑，确保计算的是移动到“栈顶”的成本。
 * ra_moves: 代表用 op_ra (向下转) 将元素移到栈顶的步数。
 * rra_moves: 代表用 op_rra (向上转) 将元素移到栈顶的步数。
 */
static int	get_cheapest_cost(t_stack *a, t_stack *b, int a_pos, int b_pos)
{
	int	ra_moves;
	int	rra_moves;
	int	rb_moves;
	int	rrb_moves;
	int	cost;

	// pos 是从栈底0开始的索引。要移到栈顶(top),
	// 向下转(ra)需要 top-pos 步，向上转(rra)需要 pos+1 步。
	ra_moves = a->top - a_pos;
	rra_moves = a_pos + 1;
	rb_moves = b->top - b_pos;
	rrb_moves = b_pos + 1;
	// 组合1: rr (A和B都向下转)
	cost = (ra_moves > rb_moves ? ra_moves : rb_moves);
	// 组合2: rrr (A和B都向上转)
	if ((rra_moves > rrb_moves ? rra_moves : rrb_moves) < cost)
		cost = (rra_moves > rrb_moves ? rra_moves : rrb_moves);
	// 组合3: ra + rrb (A向下, B向上)
	if ((ra_moves + rrb_moves) < cost)
		cost = ra_moves + rrb_moves;
	// 组合4: rra + rb (A向上, B向下)
	if ((rra_moves + rb_moves) < cost)
		cost = rra_moves + rb_moves;
	return (cost);
}

/*
 * find_best_move: 遍历 B 栈，找到移动成本最低的元素
 */
void	find_best_move(t_stack *a, t_stack *b, int *a_pos, int *b_pos)
{
	int	current_b_pos;
	int	current_a_pos;
	int	cost;
	int	min_cost;

	current_b_pos = 0;
	min_cost = INT_MAX;
	while (current_b_pos <= b->top)
	{
		current_a_pos = get_target_pos_a(a, b->storage[current_b_pos]);
		cost = get_cheapest_cost(a, b, current_a_pos, current_b_pos);
		if (cost < min_cost)
		{
			min_cost = cost;
			*a_pos = current_a_pos;
			*b_pos = current_b_pos;
		}
		current_b_pos++;
	}
}
