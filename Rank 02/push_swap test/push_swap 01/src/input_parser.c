/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:34:45 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 14:56:46 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h" // 包含所有需要的头文件，特别是 t_stack 和 INT_MAX/INT_MIN

// 辅助函数：将字符串转换为整数，并进行严格的错误检查
// 这是一个内部辅助函数，因为它是 static
static int	ft_atoi_and_check(const char *str, t_stack *a_ref)
{
	long long num; // 使用 long long 来存储中间结果，防止在转换过程中溢出 int 范围
	int sign;      // 符号位，1表示正数，-1表示负数
	int i;         // 循环索引
	num = 0;
	sign = 1;
	i = 0;
	// 1. 处理正负号
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++; // 移动到下一个字符
	}
	// 2. 检查字符串是否为空或只包含符号
	if (!str[i]) // 如果当前字符是字符串的结束符 '\0'
	{
		fprintf(stderr, "Error: Invalid input number format.\n");
		// 打印错误信息到标准错误流
		exit(EXIT_FAILURE); // 终止程序，返回失败状态
	}
	// 3. 遍历字符串，进行数字转换和溢出检查
	while (str[i]) // 只要当前字符不是字符串结束符 '\0'
	{
		if (str[i] < '0' || str[i] > '9') // 检查是否为数字字符
		{
			fprintf(stderr, "Error: Invalid characters in input.\n");
			exit(EXIT_FAILURE);
		}
		// 将字符 '0'-'9' 转换为对应的数字 0-9，并累加到 num
		num = num * 10 + (str[i] - '0');
		// 检查溢出：提前判断是否会超出 int 范围
		// 因为 num 是 long long，可以先进行乘法和加法，再与 INT_MAX/INT_MIN 比较
		if ((num * sign) > INT_MAX || (num * sign) < INT_MIN)
		{
			fprintf(stderr, "Error: Number out of integer range.\n");
			exit(EXIT_FAILURE);
		}
		i++; // 移动到下一个字符
	}
	// 4. 检查重复数字 (这需要遍历已填充的栈 A)
	// 只有当 a_ref 存在且栈中已经有元素时才进行检查
	if (a_ref && a_ref->stack_size > 0)
	{
		int k = 0; // 内部循环变量
		while (k < a_ref->stack_size)
		{
			if (a_ref->storage[k] == (int)(num * sign)) // 比较当前转换的数字与栈中已有的数字
			{
				fprintf(stderr, "Error: Duplicate numbers in input.\n");
				exit(EXIT_FAILURE);
			}
			k++;
		}
	}
	// 返回最终转换并经过检查的整数
	return ((int)(num * sign));
}

// parse_input 函数：解析命令行参数，返回一个包含所有整数的动态分配数组
// 参数: argc - 参数数量
//       argv - 参数字符串数组
//       a_ref - 栈 A 的引用 (用于传递给 ft_atoi_and_check 检查重复数字)
// 返回值: 包含解析后整数的动态分配数组 (需要在使用后 free)
int	*parse_input(int argc, char **argv, t_stack *a_ref)
{
	int *nums; // 内部工作变量：用于存储解析后的数字的数组指针
	int i;     // 循环变量：遍历 argv
	int k;     // 循环变量：nums 数组的索引
	// 1. 为存储所有数字的数组分配内存
	// argc - 1 是因为 argv[0] 是程序名，实际数字从 argv[1] 开始
	nums = (int *)malloc((argc - 1) * sizeof(int));
	if (nums == NULL)
	{
		fprintf(stderr,
			"Error: Memory allocation failed for parsed numbers.\n");
		exit(EXIT_FAILURE);
	}
	// 2. 遍历命令行参数，进行转换和检查
	i = 1; // 从 argv[1] 开始，因为 argv[0] 是程序名
	k = 0; // nums 数组从索引 0 开始填充
	while (i < argc)
	{
		// 调用辅助函数进行转换、溢出和重复数字检查
		nums[k] = ft_atoi_and_check(argv[i], a_ref);
		k++; // nums 数组索引递增
		i++; // argv 数组索引递增
	}
	return (nums); // 返回包含所有数字的数组
}

// fill_a 函数：将解析后的数字填充到栈 A
// 参数: a - 栈 A 的指针
//       nums - 包含要填充的数字的数组 (由 parse_input 返回)
//       count - 数字的数量 (也就是 argc - 1)
void	fill_a(t_stack *a, int *nums, int count)
{
	int i; // 循环变量
	// 1. 基本的空指针检查
	if (a == NULL || nums == NULL)
	{
		fprintf(stderr, "Error: Null pointer passed to fill_a.\n");
		exit(EXIT_FAILURE);
	}
	// 2. 检查栈 A 的容量是否足够（通常在 init_stack_arr 时就保证了）
	if (a->capacity < count)
	{
		fprintf(stderr, "Error: Stack A capacity too small for input.\n");
		exit(EXIT_FAILURE);
	}
	// 3. 填充栈 A 的 storage 数组
	i = 0;
	while (i < count)
	{
		a->storage[i] = nums[i]; // 将数字按顺序放入栈的 storage 数组
		a->top = i;              // 每次放入后，top 都指向当前最后一个放入的元素（即栈顶）
		a->stack_size++;         // 栈的大小递增
		i++;
	}
	// 4. 释放由 parse_input 分配的临时数组内存 (非常重要，防止内存泄漏)
	free(nums);
}
