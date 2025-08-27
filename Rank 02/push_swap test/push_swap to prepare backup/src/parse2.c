/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/15 17:54:13 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static long long	parse_digits(const char *str, int *i, bool *error)
{
	long long	num;
	int			digits_found;

	num = 0;
	digits_found = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		digits_found = 1;
		num = num * 10 + (str[*i] - '0');
		if (num > INT_MAX)
		{
			*error = true;
			return (0);
		}
		(*i)++;
	}
	if (digits_found == 0)
		*error = true;
	return (num);
}

int	ft_atoi_checked(const char *str, bool *error)
{
	long long	num;
	int			sign;
	int			i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	num = parse_digits(str, &i, error);
	if (*error)
		return (0);
	if (sign == -1 && (-num < INT_MIN))
		*error = true;
	if (str[i] != '\0' && str[i] != ' ' && !(str[i] >= '\t' && str[i] <= '\r'))
		*error = true;
	return ((int)(num * sign));
}

int	count_words(const char *str)
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

static void	check_inner_loop(int *nums, int count, int i)
{
	int	j;

	j = i + 1;
	while (j < count)
	{
		if (nums[i] == nums[j])
		{
			free(nums);
			write(2, "Error\n", 6);
			exit(EXIT_FAILURE);
		}
		j++;
	}
}

void	check_duplicates(int *nums, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		check_inner_loop(nums, count, i);
		i++;
	}
}
