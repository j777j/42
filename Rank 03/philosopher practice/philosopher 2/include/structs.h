#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long long		last_meal_time;
	int				meal_count;
	struct s_data	*data;
	pthread_t		thread;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				num_meals;
	long long		start_time;
	int				num_philos_done_eating;
	int				all_philos_done;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	data_mutex;
	t_philo			*philos;
}					t_data;

#endif
