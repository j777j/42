/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:39:31 by juwang            #+#    #+#             */
/*   Updated: 2025/07/31 15:41:16 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	handle_one_philosopher(t_data *data)
{
	data->start_time = get_time();
	printf("%lld 1 has taken a fork\n", get_time() - data->start_time);
	usleep(data->time_to_die * 1000);
	printf("%lld 1 died\n", get_time() - data->start_time);
}

int	main(int argc, char **argv)
{
	t_data data;
	pthread_t monitor_thread;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo num_philos time_to_die time_to_eat "
				"time_to_sleep [num_meals]\n");
		return (1);
	}
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (init_philos(&data) != 0)
		return (1);
	if (init_mutexes(&data) != 0)
		return (1);
	if (data.num_philos == 1)
	{
		handle_one_philosopher(&data);
		cleanup(&data);
		return (0);
	}
	start_threads(&data);
	pthread_create(&monitor_thread, NULL, &monitor_routine, &data);
	join_threads(&data);
	pthread_join(monitor_thread, NULL);
	cleanup(&data);
	return (0);
}
