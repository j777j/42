/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:39:47 by juwang            #+#    #+#             */
/*   Updated: 2025/08/02 20:30:27 by juwang           ###   ########.fr       */
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

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = &philo->data->forks[philo->left_fork];
	second_fork = &philo->data->forks[philo->right_fork];
	if (philo->id % 2 == 0)
	{
		first_fork = &philo->data->forks[philo->right_fork];
		second_fork = &philo->data->forks[philo->left_fork];
	}
	pthread_mutex_lock(first_fork);
	print_status(philo, "has taken a fork");
	if (philo->data->num_philos == 1)
	{
		precise_sleep(philo->data->time_to_die * 2, philo->data);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	print_status(philo, "has taken a fork");
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
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
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
		if (philo->data->num_philos % 2 != 0)
			usleep(250);
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

void	start_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].philo_mutex);
		data->philos[i].last_meal_time = data->start_time;
		pthread_mutex_unlock(&data->philos[i].philo_mutex);
		pthread_create(&data->philos[i].thread, NULL, &philosopher_routine,
			&data->philos[i]);
		i++;
	}
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->data_mutex);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}
