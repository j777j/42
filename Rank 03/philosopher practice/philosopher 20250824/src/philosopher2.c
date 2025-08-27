/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:23:39 by juwang            #+#    #+#             */
/*   Updated: 2025/08/23 18:29:14 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	get_fork_order(t_philo *p, int *first, int *second)
{
	if (p->left_fork < p->right_fork)
	{
		*first = p->left_fork;
		*second = p->right_fork;
	}
	else
	{
		*first = p->right_fork;
		*second = p->left_fork;
	}
}

static void	eating_action_and_update(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->philo_mutex);
	print_status(philo, "is eating");
	if (philo->data->num_meals > 0
		&& philo->meal_count == philo->data->num_meals)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		philo->data->num_philos_done_eating++;
		pthread_mutex_unlock(&philo->data->data_mutex);
	}
	precise_sleep(philo->data->time_to_eat, philo->data);
}

void	philo_eat(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
		precise_sleep(philo->data->time_to_die * 2, philo->data);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return ;
	}
	get_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	print_status(philo, "has taken a fork");
	eating_action_and_update(philo);
	pthread_mutex_unlock(&philo->data->forks[second_fork]);
	pthread_mutex_unlock(&philo->data->forks[first_fork]);
}
