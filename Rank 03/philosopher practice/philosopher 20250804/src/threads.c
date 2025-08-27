/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 23:40:54 by juwang            #+#    #+#             */
/*   Updated: 2025/08/02 23:40:55 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	start_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].philo_mutex);
		data->philos[i].last_meal_time = data->start_time;
		pthread_mutex_unlock(&data->philos[i].philo_mutex);
		if (pthread_create(&data->philos[i].thread, NULL, &philosopher_routine,
				&data->philos[i]) != 0)
			return ; // Should handle errors more gracefully
		i++;
	}
	if (pthread_create(&data->monitor_thread, NULL, &monitor_routine,
			data) != 0)
		return ; // Should handle errors more gracefully
}

void	join_threads(t_data *data)
{
	int i;

	i = 0;
	pthread_join(data->monitor_thread, NULL);
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
