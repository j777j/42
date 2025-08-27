/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:39:39 by juwang            #+#    #+#             */
/*   Updated: 2025/07/26 18:39:40 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor_checks.h"

int	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->data_mutex);
		if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
		{
			print_status(&data->philos[i], "died");
			data->all_philos_done = 1;
			pthread_mutex_unlock(&data->data_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->data_mutex);
		i++;
	}
	return (0);
}

int	check_all_meals_done(t_data *data)
{
	pthread_mutex_lock(&data->data_mutex);
	if (data->num_philos_done_eating == data->num_philos)
	{
		pthread_mutex_unlock(&data->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (0);
}
