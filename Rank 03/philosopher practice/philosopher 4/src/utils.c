/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:39:51 by juwang            #+#    #+#             */
/*   Updated: 2025/08/02 19:00:27 by juwang           ###   ########.fr       */
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
		usleep(100);
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

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
