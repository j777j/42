/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:17:53 by juwang            #+#    #+#             */
/*   Updated: 2025/08/02 23:39:40 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct s_data;

typedef struct s_philo
{
	int				id;
	long long		last_meal_time;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t philo_mutex; // Protects last_meal_time and meals_eaten
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				num_must_eat;
	long long		start_time;
	int				is_dead;
	int				all_philos_done;
	pthread_t		monitor_thread;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t data_mutex; // Protects is_dead and all_philos_done
}					t_data;

// Function Prototypes
long long			get_time(void);
void				precise_sleep(long long duration);
void				print_status(t_philo *philo, char *status);
int					ft_atoi(const char *str);

int					init_data(t_data *data, int argc, char **argv);
int					init_mutexes(t_data *data);
int					init_philos(t_data *data);

void				*philosopher_routine(void *arg);
void				*monitor_routine(void *arg);

void				start_threads(t_data *data);
void				join_threads(t_data *data);
void				cleanup(t_data *data);
void				handle_one_philosopher(t_data *data);
int					simulation_finished(t_data *data);

#endif
