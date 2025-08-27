/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:39:39 by juwang            #+#    #+#             */
/*   Updated: 2025/08/02 17:15:27 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	handle_death(t_data *data, int i, long long time)
{
	pthread_mutex_lock(&data->data_mutex);
	if (data->all_philos_done)
	{
		pthread_mutex_unlock(&data->data_mutex);
		return (1);
	}
	data->all_philos_done = 1;
	printf("%lld %d died\n", time - data->start_time,
		data->philos[i].id);
	pthread_mutex_unlock(&data->data_mutex);
	return (1);
}

int	check_death(t_data *data)
{
	int			i;
	long long	time;
	long long	last_meal;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].philo_mutex);
		last_meal = data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->philos[i].philo_mutex);
		time = get_time();
		if (time - last_meal > data->time_to_die)
			return (handle_death(data, i, time));
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
