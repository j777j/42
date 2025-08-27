/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:27:08 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 07:48:33 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/*
 * swap: 交换栈顶的两个元素
 *
 * 功能:
 * 如果栈中至少有两个元素，就交换索引 top 和 top-1 的值。
 * 这是一个内部辅助函数。
 */
static void	swap(t_stack *stack)
{
	int	tmp;

	if (stack == NULL || stack->stack_size < 2)
		return ;
	tmp = stack->storage[stack->top];
	stack->storage[stack->top] = stack->storage[stack->top - 1];
	stack->storage[stack->top - 1] = tmp;
}

/*
 * op_sa: 交换 A 栈顶的两个元素
 */
void	op_sa(t_stack *a, bool print)
{
	swap(a);
	if (print)
		write(1, "sa\n", 3);
}

/*
 * op_sb: 交换 B 栈顶的两个元素
 */
void	op_sb(t_stack *b, bool print)
{
	swap(b);
	if (print)
		write(1, "sb\n", 3);
}

/*
 * op_ss: 同时执行 sa 和 sb
 */
void	op_ss(t_stack *a, t_stack *b, bool print)
{
	swap(a);
	swap(b);
	if (print)
		write(1, "ss\n", 3);
}
