/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:39:47 by juwang            #+#    #+#             */
/*   Updated: 2025/08/02 23:40:14 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->philo_mutex);
	print_status(philo, "is eating");
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->philo_mutex);
	precise_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!simulation_finished(philo->data))
	{
		philo_eat(philo);
		if (simulation_finished(philo->data))
			break ;
		print_status(philo, "is sleeping");
		precise_sleep(philo->data->time_to_sleep);
		if (simulation_finished(philo->data))
			break ;
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	handle_one_philosopher(t_data *data)
{
	data->start_time = get_time();
	printf("%lld 1 has taken a fork\n", get_time() - data->start_time);
	usleep(data->time_to_die * 1000);
	printf("%lld 1 died\n", get_time() - data->start_time);
}
