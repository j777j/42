/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:39:44 by juwang            #+#    #+#             */
/*   Updated: 2025/07/26 18:39:45 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_actions.h"

void	eat(t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_meal_time = get_time();
	philo->meal_count++;
	if (philo->meal_count == philo->data->num_meals)
		philo->data->num_philos_done_eating++;
	pthread_mutex_unlock(&philo->data->data_mutex);
	usleep(philo->data->time_to_eat * 1000);
}
