/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 08:29:07 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 08:34:51 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
 * ft_atoi_checked: 一个带严格错误检查的字符串转整数函数
 *
 * 功能:
 * 1. 将字符串转换为 long long 类型以防止转换过程中的溢出。
 * 2. 检查转换后的数字是否在 int 范围内。
 * 3. 检查字符串中是否包含非数字字符。
 *
 * 参数:
 * str:   要转换的字符串。
 * error: 指向一个布尔值的指针，如果发生错误，这个布尔值会被设为 true。
 *
 * 返回值:
 * 转换后的整数。如果发生错误，返回值无意义，但 error 会被设为 true。
 */
static int	ft_atoi_checked(const char *str, bool *error)
{
	long long	num;
	int			sign;
	int			i;

	num = 0;
	sign = 1;
	i = 0;
	// 跳过开头的空白字符
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	// 处理正负号
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	// 核心转换逻辑
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		// 关键的溢出检查
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && -num < INT_MIN))
		{
			*error = true;
			return (0);
		}
		i++;
	}
	// 检查字符串末尾是否有多余的非数字字符
	if (str[i] != '\0')
		*error = true;
	return ((int)(num * sign));
}

/*
 * parse_and_validate_input: 解析所有命令行参数并进行验证
 *
 * 功能:
 * 1. 遍历所有输入参数。
 * 2. 使用 ft_atoi_checked 进行转换和单项检查。
 * 3. 检查所有数字中是否有重复项。
 *
 * 参数:
 * argc:  参数数量。
 * argv:  参数字符串数组。
 * count: 指向一个整数的指针，用于传回有效的数字数量。
 *
 * 返回值:
 * 一个动态分配的、包含所有有效整数的数组。如果出错，程序会退出。
 */
int	*parse_and_validate_input(int argc, char **argv, int *count)
{
	int		*nums;
	int		i;
	int		j;
	bool	error;

	*count = argc - 1;
	// 为存储整数的数组分配内存
	nums = (int *)malloc(sizeof(int) * (*count));
	if (nums == NULL)
		exit(EXIT_FAILURE);
	error = false;
	i = 0;
	while (i < *count)
	{
		nums[i] = ft_atoi_checked(argv[i + 1], &error);
		if (error)
		{
			free(nums);
			// 在最终版本中，这里应该调用一个打印 "Error" 消息的函数
			exit(EXIT_FAILURE);
		}
		// 检查重复数字
		j = 0;
		while (j < i)
		{
			if (nums[j] == nums[i])
			{
				free(nums);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (nums);
}
