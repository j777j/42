/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:27:10 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 07:48:50 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/*
 * push: 将一个元素从源栈顶推到目标栈顶
 *
 * 功能:
 * 这是一个内部辅助函数。
 */
static void	push(t_stack *dest, t_stack *src)
{
	int	val_to_push;

	if (src == NULL || src->stack_size == 0)
		return ;
	// 1. 从源栈“弹出”值
	val_to_push = src->storage[src->top];
	src->top--;
	src->stack_size--;
	// 2. 将值“推入”目标栈
	dest->top++;
	dest->storage[dest->top] = val_to_push;
	dest->stack_size++;
}

/*
 * op_pa: 将 B 栈顶元素推到 A 栈顶
 */
void	op_pa(t_stack *a, t_stack *b, bool print)
{
	push(a, b);
	if (print)
		write(1, "pa\n", 3);
}

/*
 * op_pb: 将 A 栈顶元素推到 B 栈顶
 */
void	op_pb(t_stack *a, t_stack *b, bool print)
{
	push(b, a);
	if (print)
		write(1, "pb\n", 3);
}
