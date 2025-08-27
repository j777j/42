/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:28:27 by yohasega          #+#    #+#             */
/*   Updated: 2025/08/04 11:42:07 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_data *data)
{
	int i;

	if (data->must_eat == 0)
		return ;
	start_delay(data->start_time);
	while (1)
	{
		i = 0;
		while (i < data->philos_num)
		{
			if (check_anyone_dead(data, i))
				return ;
			i++;
		}
		if (everyone_is_full(data))
			return ;
		usleep(300);
	}
}
