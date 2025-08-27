/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:16:42 by yohasega          #+#    #+#             */
/*   Updated: 2025/08/04 12:22:52 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_create(&data->philos[i].philo, NULL, &routine,
				&data->philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_detach(data->philos[i].philo);
			error_free("pthread_join error\n", data);
			return ;
		}
		i++;
	}
	monitor(data);
	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_join(data->philos[i].philo, NULL) != 0)
			error_msg("pthread_join error\n");
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!validate(ac, av))
		return (EXIT_FAILURE);
	if (init_data(&data, ac, av))
		return (EXIT_FAILURE);
	philosophers(&data);
	destroy_all(&data);
	free_data(&data);
	return (EXIT_SUCCESS);
}
