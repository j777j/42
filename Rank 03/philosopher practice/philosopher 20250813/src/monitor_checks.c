/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:39:39 by juwang            #+#    #+#             */
/*   Updated: 2025/08/13 16:20:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_philosopher_dead(t_philo *philo, t_data *data)
{
	long long	time;
	long long	last_meal;

	pthread_mutex_lock(&philo->philo_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->philo_mutex);
	time = get_time();
	if (time - last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->data_mutex);
		if (data->all_philos_done)
		{
			pthread_mutex_unlock(&data->data_mutex);
			return (1);
		}
		data->all_philos_done = 1;
		printf("%lld %d died\n", time - data->start_time, philo->id);
		pthread_mutex_unlock(&data->data_mutex);
		return (1);
	}
	return (0);
}

int	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (is_philosopher_dead(&data->philos[i], data))
			return (1);
		i++;
	}
	return (0);
}

int	check_all_meals_done(t_data *data)
{
	int	all_done;

	all_done = 0;
	pthread_mutex_lock(&data->data_mutex);
	if (data->num_meals > 0
		&& data->num_philos_done_eating >= data->num_philos)
	{
		if (!data->all_philos_done)
		{
			data->all_philos_done = 1;
			all_done = 1;
		}
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (all_done);
}
