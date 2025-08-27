/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:49:09 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 14:56:03 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h" // 包含所有需要的头文件

// insertion_sort 函数：对一个整数数组进行升序排序
// 参数: arr - 指向要排序的整数数组的指针
//       size - 数组中元素的数量
void	insertion_sort(int *arr, int size)
{
	int i;   // 内部工作变量：外层循环的索引，表示当前待插入的元素
	int key; // 内部工作变量：当前待插入的元素的值
	int j;   // 内部工作变量：内层循环的索引，用于比较和移动元素
	// 从数组的第二个元素开始遍历 (索引 1)
	// 因为第一个元素 (索引 0) 可以被认为是已排序部分的开始
	i = 1;
	while (i < size)
	{
		key = arr[i]; // 将当前待插入的元素保存到 key 变量中
		j = i - 1;    // 从已排序部分的最后一个元素开始向前比较
		// 将比 key 大的元素向后移动一位
		// j >= 0 确保不越界
		// arr[j] > key 表示找到一个比 key 大的元素
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j]; // 将 arr[j] (较大的元素) 向后移动到 arr[j+1]
			j--;                 // 向前移动到下一个元素
		}
		arr[j + 1] = key; // 将 key (当前待插入的元素) 插入到正确的位置
		i++;              // 移动到下一个待插入的元素
	}
}

// gen_sorted_arr 函数：生成一个包含栈中所有元素且已排序的新数组
// 参数: stack - 指向要处理的栈的指针 (通常是 A 栈)
// 返回值: 指向已排序整数数组的指针。如果内存分配失败，程序将退出。
int	*gen_sorted_arr(t_stack *stack)
{
	int *sorted_arr; // 内部工作变量：指向新的、将要排序的数组
	int i;           // 循环索引
	// 1. 为新数组分配内存，大小与栈中当前元素数量相同
	sorted_arr = (int *)malloc(stack->stack_size * sizeof(int));
	if (sorted_arr == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed for sorted array.\n");
		exit(EXIT_FAILURE);
	}
	// 2. 将栈中的所有元素复制到新数组中
	i = 0;
	while (i < stack->stack_size)
	{
		sorted_arr[i] = stack->storage[i]; // 将栈的 storage[i] 复制到 sorted_arr[i]
		i++;
	}
	// 3. 对新数组进行排序
	insertion_sort(sorted_arr, stack->stack_size);
	// 4. 返回排序后的数组
	return (sorted_arr);
}

// simplify_numbers 函数：将栈中的原始数字替换为它们的等级 (0 到 N-1)
// 参数: stack - 指向要处理的栈的指针 (A 栈)
//       sorted_arr - 指向已排序的临时数组 (由 gen_sorted_arr 返回，此函数会负责 free 掉它)
void	simplify_numbers(t_stack *stack, int *sorted_arr)
{
	int *temp_ranks; // 内部工作变量：临时数组，用于存储计算出的等级
	int i;           // 循环索引：遍历栈的原始数字
	int j;           // 循环索引：遍历排序后的数组
	// 1. 为临时等级数组分配内存
	temp_ranks = (int *)malloc(stack->stack_size * sizeof(int));
	if (temp_ranks == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed for temp_ranks.\n");
		exit(EXIT_FAILURE);
	}
	// 2. 计算每个原始数字的等级
	// 遍历栈 A 中的每个原始数字
	i = 0;
	while (i < stack->stack_size)
	{
		// 遍历排序后的数组，找到当前原始数字的等级
		j = 0;
		while (j < stack->stack_size)
		{
			// 如果栈中的原始数字等于排序后数组中的某个数字
			if (stack->storage[i] == sorted_arr[j])
			{
				// 那么它的等级就是 sorted_arr 中的索引 j
				temp_ranks[i] = j;
				break ; // 找到后立即跳出内层循环
			}
			j++;
		}
		i++;
	}
	// 3. 将栈 A 中的原始数字替换为它们的等级
	i = 0;
	while (i < stack->stack_size)
	{
		stack->storage[i] = temp_ranks[i]; // 将原始数字替换为计算出的等级
		i++;
	}
	// 4. 释放临时内存
	free(temp_ranks); // 释放临时等级数组
	free(sorted_arr); // 释放排序后的原始数字数组 (由 gen_sorted_arr 分配)
}
