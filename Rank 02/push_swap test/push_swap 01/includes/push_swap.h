/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:41:46 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 14:57:09 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>  // 用于整数的最大最小值检查 (INT_MAX, INT_MIN)
# include <stdbool.h> // 用于布尔类型 (true, false)
# include <stdio.h>   // 用于调试输出或错误信息 (printf, fprintf)
# include <stdlib.h>  // 用于内存分配 (malloc, free)
# include <unistd.h>  // 可能用于写入操作 (write)

typedef struct s_stack
//给struct s_stack 取了一个更方便的昵称 t_stack。以后，当想要声明一个栈变量时，就可以直接用 t_stack 了。
{
	int *storage; // 这是一个指向整数数组的指针。所有栈里的数字都存在这个数组里。
					// 这里的 'int *' 是我们刚刚学过的“指针”类型。
					// 'storage' 这个变量存储的是栈中实际存放数字的那个“数组”的内存地址。

	int top; // 栈顶元素的索引。例如，如果栈里有3个元素，它们的索引是0, 1, 2，那么 top 就是2。
				// 这里的 'int' 是我们刚刚学过的“整数”数据类型。
				// 'top' 这个变量存储的就是一个整数值，代表当前栈顶的位置。

	int capacity; // 这个栈（也就是底层的数组）能存放的最大元素数量。
					// 这里的 'int' 也是“整数”数据类型。
					// 'capacity' 存储的是这个数组“最大能装多少东西”的整数值。

	int stack_size; // 栈中当前实际元素的数量。
					// 这里的 'int' 也是“整数”数据类型。
					// 'stack_size' 存储的是这个栈“目前装了多少东西”的整数值。
					// 它和 top 有关系，如果栈不为空，通常 stack_size 就等于 top+ 1。
}	t_stack;

typedef struct s_push_swap
{
	t_stack *a; // 指向 A 栈的指针
	t_stack *b; // 指向 B 栈的指针
				// 这里的 't_stack *' 也是“指针”类型，它指向的是我们上面定义的 't_stack' 结构体的内存地址。
}	t_push_swap;

#endif
