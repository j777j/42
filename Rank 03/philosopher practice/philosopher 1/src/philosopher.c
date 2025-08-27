#include "philosopher.h"
#include "philo_actions.h"
#include "monitor_checks.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (!philo->data->all_philos_done)
	{
		print_status(philo, "is thinking");
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->all_philos_done)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (check_death(data, i))
				break ;
			i++;
		}
		if (data->num_meals != -1 && check_all_meals_done(data))
			data->all_philos_done = 1;
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
		data->philos[i].last_meal_time = data->start_time;
		pthread_create(&data->philos[i].thread, NULL, &philosopher_routine, &data->philos[i]);
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
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->data_mutex);
	free(data->philos);
	free(data->forks);
}
