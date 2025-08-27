/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_free_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:21:18 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 15:21:29 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h" // 包含所有需要的头文件

// free_stacks_arr 函数：释放两个数组栈的所有内存
// 参数: a - 指向 A 栈的指针
//       b - 指向 B 栈的指针
void	free_stacks_arr(t_stack *a, t_stack *b)
{
	// 1. 释放 A 栈的内存
	if (a != NULL) // 确保 A 栈指针不为空
	{
		if (a->storage != NULL) // 如果 A 栈的 storage 数组已分配
		{
			free(a->storage);  // 释放 storage 数组内存
			a->storage = NULL; // 将指针设为 NULL，防止悬空指针
		}
		free(a);  // 释放 t_stack 结构体本身的内存
		a = NULL; // 将传入的指针设为 NULL (尽管这不会影响调用者的指针副本)
	}

	// 2. 释放 B 栈的内存 (与 A 栈逻辑相同)
	if (b != NULL)
	{
		if (b->storage != NULL)
		{
			free(b->storage);
			b->storage = NULL;
		}
		free(b);
		b = NULL;
	}
}
