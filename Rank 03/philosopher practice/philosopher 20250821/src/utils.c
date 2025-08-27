/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:39:51 by juwang            #+#    #+#             */
/*   Updated: 2025/08/23 18:04:24 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep(long long duration, t_data *data)
{
	long long	start;

	start = get_time();
	while (1)
	{
		pthread_mutex_lock(&data->data_mutex);
		if (data->all_philos_done)
		{
			pthread_mutex_unlock(&data->data_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->data_mutex);
		if (get_time() - start >= duration)
			break ;
		usleep(500);
	}
}

void	print_status(t_philo *philo, char *status)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->data_mutex);
	if (!philo->data->all_philos_done)
	{
		time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

static bool	parse_and_convert(const char *str, long long *res, int *s)
{
	int	i;

	*res = 0;
	*s = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (*res > INT_MAX / 10 || (*res == INT_MAX / 10 && (str[i]
					- '0') > INT_MAX % 10))
			return (false);
		*res = *res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (false);
	return (true);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	if (!parse_and_convert(str, &result, &sign))
	{
		return (0);
	}
	return ((int)result * sign);
}
