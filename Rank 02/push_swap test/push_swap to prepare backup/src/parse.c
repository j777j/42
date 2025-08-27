/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:36:41 by juwang            #+#    #+#             */
/*   Updated: 2025/07/15 17:51:51 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	*parse_from_string(const char *str, int *count);
static int	*parse_from_args(int argc, char **argv, int *count);

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

static bool	parse_string_loop(const char **str, int *nums, int count, bool *err)
{
	int	i;

	i = 0;
	while (i < count)
	{
		while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
			(*str)++;
		if (**str)
			nums[i] = ft_atoi_checked(*str, err);
		if (*err)
		{
			free(nums);
			return (false);
		}
		while (**str && (**str != ' ' && !(**str >= '\t' && **str <= '\r')))
			(*str)++;
		i++;
	}
	return (true);
}

static int	*parse_from_string(const char *str, int *count)
{
	int		*nums;
	bool	error;

	*count = count_words(str);
	if (*count == 0)
		return (NULL);
	nums = (int *)malloc(sizeof(int) * (*count));
	if (nums == NULL)
		return (NULL);
	error = false;
	if (!parse_string_loop(&str, nums, *count, &error))
		return (NULL);
	return (nums);
}
