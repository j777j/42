#include "monitor_checks.h"

int	check_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->data_mutex);
	if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
	{
		print_status(&data->philos[i], "died");
		data->all_philos_done = 1;
		pthread_mutex_unlock(&data->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (0);
}

int	check_all_meals_done(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->data_mutex);
		if (data->num_meals != -1 && data->philos[i].meal_count < data->num_meals)
		{
			pthread_mutex_unlock(&data->data_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->data_mutex);
		i++;
	}
	return (1);
}
