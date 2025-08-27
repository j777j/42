/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:39:31 by juwang            #+#    #+#             */
/*   Updated: 2025/07/26 18:39:33 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"
#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (init_philos(&data) != 0)
		return (1);
	if (init_mutexes(&data) != 0)
		return (1);
	start_threads(&data);
	pthread_create(&monitor_thread, NULL, &monitor_routine, &data);
	join_threads(&data);
	pthread_join(monitor_thread, NULL);
	cleanup(&data);
	return (0);
}
