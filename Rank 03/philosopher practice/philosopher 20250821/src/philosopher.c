/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:21:47 by juwang            #+#    #+#             */
/*   Updated: 2025/08/23 18:31:29 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	simulation_should_end(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->data->data_mutex);
	ret = philo->data->all_philos_done;
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (ret);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_sleep(philo->data->time_to_eat / 2, philo->data);
	while (!simulation_should_end(philo))
	{
		philo_eat(philo);
		if (simulation_should_end(philo))
			break ;
		print_status(philo, "is sleeping");
		precise_sleep(philo->data->time_to_sleep, philo->data);
		if (simulation_should_end(philo))
			break ;
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data) || check_all_meals_done(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}
