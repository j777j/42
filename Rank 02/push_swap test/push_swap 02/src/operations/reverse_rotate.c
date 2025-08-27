/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:27:15 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 07:48:46 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/*
 * reverse_rotate: 将栈底元素移到栈顶
 *
 * 功能:
 * 这是一个内部辅助函数。
 */
static void	reverse_rotate(t_stack *stack)
{
	int	tmp;
	int	i;

	if (stack == NULL || stack->stack_size < 2)
		return ;
	// 1. 保存栈底元素
	tmp = stack->storage[0];
	// 2. 将所有元素向上移动一位
	i = 0;
	while (i < stack->top)
	{
		stack->storage[i] = stack->storage[i + 1];
		i++;
	}
	// 3. 将原栈底元素放到栈顶
	stack->storage[stack->top] = tmp;
}

/*
 * op_rra: 反向旋转 A 栈
 */
void	op_rra(t_stack *a, bool print)
{
	reverse_rotate(a);
	if (print)
		write(1, "rra\n", 3);
}

/*
 * op_rrb: 反向旋转 B 栈
 */
void	op_rrb(t_stack *b, bool print)
{
	reverse_rotate(b);
	if (print)
		write(1, "rrb\n", 3);
}

/*
 * op_rrr: 同时反向旋转 A 和 B 栈
 */
void	op_rrr(t_stack *a, t_stack *b, bool print)
{
	reverse_rotate(a);
	reverse_rotate(b);
	if (print)
		write(1, "rrr\n", 3);
}
