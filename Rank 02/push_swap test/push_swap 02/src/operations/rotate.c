/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:27:12 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 07:48:38 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/*
 * rotate: 将栈顶元素移到栈底
 *
 * 功能:
 * 这是一个内部辅助函数。
 */
static void	rotate(t_stack *stack)
{
	int	tmp;
	int	i;

	if (stack == NULL || stack->stack_size < 2)
		return ;
	// 1. 保存栈顶元素
	tmp = stack->storage[stack->top];
	// 2. 将所有元素向下移动一位
	i = stack->top;
	while (i > 0)
	{
		stack->storage[i] = stack->storage[i - 1];
		i--;
	}
	// 3. 将原栈顶元素放到栈底 (索引0)
	stack->storage[0] = tmp;
}

/*
 * op_ra: 旋转 A 栈
 */
void	op_ra(t_stack *a, bool print)
{
	rotate(a);
	if (print)
		write(1, "ra\n", 3);
}

/*
 * op_rb: 旋转 B 栈
 */
void	op_rb(t_stack *b, bool print)
{
	rotate(b);
	if (print)
		write(1, "rb\n", 3);
}

/*
 * op_rr: 同时旋转 A 和 B 栈
 */
void	op_rr(t_stack *a, t_stack *b, bool print)
{
	rotate(a);
	rotate(b);
	if (print)
		write(1, "rr\n", 3);
}
