/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:39:31 by juwang            #+#    #+#             */
/*   Updated: 2025/08/02 23:39:50 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_data data;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo num_philos time_to_die time_to_eat "
				"time_to_sleep [num_meals]\n");
		return (1);
	}
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (init_mutexes(&data) != 0)
		return (1);
	if (init_philos(&data) != 0)
		return (1);
	if (data.num_philos == 1)
	{
		handle_one_philosopher(&data);
		cleanup(&data);
		return (0);
	}
	start_threads(&data);
	join_threads(&data);
	cleanup(&data);
	return (0);
}
