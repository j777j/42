/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 23:40:33 by juwang            #+#    #+#             */
/*   Updated: 2025/08/02 23:40:35 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	simulation_finished(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->data_mutex);
	ret = data->is_dead || data->all_philos_done;
	pthread_mutex_unlock(&data->data_mutex);
	return (ret);
}

void	*monitor_routine(void *arg)
{
	t_data *data;
	int i;
	int philos_are_full;

	data = (t_data *)arg;
	while (!simulation_finished(data))
	{
		philos_are_full = 1;
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->philos[i].philo_mutex);
			if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
			{
				print_status(&data->philos[i], "died");
				pthread_mutex_lock(&data->data_mutex);
				data->is_dead = 1;
				pthread_mutex_unlock(&data->data_mutex);
				pthread_mutex_unlock(&data->philos[i].philo_mutex);
				return (NULL);
			}
			if (data->num_must_eat != -1
				&& data->philos[i].meals_eaten < data->num_must_eat)
				philos_are_full = 0;
			pthread_mutex_unlock(&data->philos[i].philo_mutex);
			i++;
		}
		if (data->num_must_eat != -1 && philos_are_full)
		{
			pthread_mutex_lock(&data->data_mutex);
			data->all_philos_done = 1;
			pthread_mutex_unlock(&data->data_mutex);
		}
		usleep(1000);
	}
	return (NULL);
}
