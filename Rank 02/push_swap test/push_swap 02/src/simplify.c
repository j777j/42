/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:49:09 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 07:47:51 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
 * insertion_sort: 一个简单的插入排序算法
 *
 * 功能:
 * 对一个整数数组进行原地升序排序。我们选择它是因为实现简单，
 * 并且对于我们项目开始时的一次性排序（最多500个元素），它的性能足够了。
 *
 * 参数:
 * arr:  指向要排序的整数数组的指针。
 * size: 数组中元素的数量。
 */
static void	insertion_sort(int *arr, int size)
{
	int	i;
	int	j;
	int	key;

	i = 1;
	while (i < size)
	{
		key = arr[i];
		j = i - 1;
		// 将比 key 大的元素向后移动一位，为 key 腾出空间
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
		i++;
	}
}

/*
 * simplify_numbers: 将栈中的原始数字替换为它们的等级 (0 到 N-1)
 *
 * 功能:
 * 1. 创建一个栈 A 中所有数字的临时副本。
 * 2. 对这个副本进行排序，得到一个从最小到最大的有序数组。
 * 3. 遍历原始的栈 A，对于其中的每一个数字，在排序后的数组中找到它的位置（索引）。
 * 4. 这个索引就是它的“等级”，用这个等级替换栈 A 中的原始数字。
 *
 * 参数:
 * a_stack: 指向 A 栈的指针，这个栈将被修改。
 */
void	simplify_numbers(t_stack *a_stack)
{
	int	*sorted_arr;
	int	i;
	int	j;

	// 1. 创建一个临时数组并复制 A 栈的数据
	sorted_arr = (int *)malloc(sizeof(int) * a_stack->stack_size);
	if (sorted_arr == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < a_stack->stack_size)
	{
		sorted_arr[i] = a_stack->storage[i];
		i++;
	}
	// 2. 对临时数组进行排序
	insertion_sort(sorted_arr, a_stack->stack_size);
	// 3. 根据排序后的数组，更新 A 栈中的值为它们的等级
	i = 0;
	while (i < a_stack->stack_size)
	{
		j = 0;
		while (j < a_stack->stack_size)
		{
			// 如果在排序数组中找到了原始数字
			if (a_stack->storage[i] == sorted_arr[j])
			{
				// 就用它在排序数组中的索引 j (即它的等级) 来替换它
				a_stack->storage[i] = j;
				break ; // 找到后立即跳出内层循环
			}
			j++;
		}
		i++;
	}
	// 4. 释放临时排序数组的内存
	free(sorted_arr);
}
