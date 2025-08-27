/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:36:41 by juwang            #+#    #+#             */
/*   Updated: 2025/07/08 17:53:16 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	ft_atoi_checked(const char *str, bool *error);
static void	check_duplicates(int *nums, int count);
static int	count_words(const char *str);
static int	*parse_from_string(const char *str, int *count);
static int	*parse_from_args(int argc, char **argv, int *count);

/*
 * 主解析函数，现在可以智能地处理两种输入模式
 */
int	*parse_and_validate_input(int argc, char **argv, int *count)
{
	int	*nums;

	if (argc == 2)
		nums = parse_from_string(argv[1], count);
	else
		nums = parse_from_args(argc, argv, count);
	if (nums == NULL)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	check_duplicates(nums, *count);
	return (nums);
}

/*
 * 从多个参数 (argv) 中解析数字
 */
static int	*parse_from_args(int argc, char **argv, int *count)
{
	int		*nums;
	int		i;
	bool	error;

	*count = argc - 1;
	nums = (int *)malloc(sizeof(int) * (*count));
	if (nums == NULL)
		return (NULL);
	error = false;
	i = 0;
	while (i < *count)
	{
		nums[i] = ft_atoi_checked(argv[i + 1], &error);
		if (error)
		{
			free(nums);
			return (NULL);
		}
		i++;
	}
	return (nums);
}

/*
 * 从单个字符串中解析由空格分隔的数字
 */
static int	*parse_from_string(const char *str, int *count)
{
	int		*nums;
	int		i;
	bool	error;

	*count = count_words(str);
	if (*count == 0)
		return (NULL);
	nums = (int *)malloc(sizeof(int) * (*count));
	if (nums == NULL)
		return (NULL);
	error = false;
	i = 0;
	while (i < *count)
	{
		while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
			str++;
		if (*str)
			nums[i] = ft_atoi_checked(str, &error);
		if (error)
		{
			free(nums);
			return (NULL);
		}
		while (*str && (*str != ' ' && !(*str >= '\t' && *str <= '\r')))
			str++;
		i++;
	}
	return (nums);
}

/*
 * 检查数组中是否有重复数字
 */
static void	check_duplicates(int *nums, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (nums[i] == nums[j])
			{
				write(2, "Error\n", 6);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}

/*
 * 一个带严格错误检查的字符串转整数函数 (全新健壮版)
 */
static int	ft_atoi_checked(const char *str, bool *error)
{
	long long	num;
	int			sign;
	int			i;
	int			digits_found;

	num = 0;
	sign = 1;
	i = 0;
	digits_found = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		digits_found = 1;
		num = num * 10 + (str[i] - '0');
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && -num < INT_MIN))
		{
			*error = true;
			return (0);
		}
		i++;
	}
	if (digits_found == 0)
		*error = true;
	if (str[i] != '\0' && str[i] != ' ' && !(str[i] >= '\t' && str[i] <= '\r'))
		*error = true;
	return ((int)(num * sign));
}

// 辅助函数: 计算字符串中有多少个由空格分隔的单词
static int	count_words(const char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != ' ' && !(*str >= '\t' && *str <= '\r'))
		{
			if (in_word == 0)
			{
				in_word = 1;
				count++;
			}
		}
		else
			in_word = 0;
		str++;
	}
	return (count);
}

int is_sorted_int_array(int *nums, int count)
{
    int i;
    for (i = 0; i < count - 1; i++)
    {
        if (nums[i] > nums[i + 1])
            return 0;
    }
    return 1;
}
