/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:17:53 by juwang            #+#    #+#             */
/*   Updated: 2025/08/23 18:27:01 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					left_fork;
	int					right_fork;
	int					meal_count;
	long long			last_meal_time;
	t_data				*data;
	pthread_mutex_t		philo_mutex;
}						t_philo;

typedef struct s_data
{
	int					num_philos;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					num_meals;
	int					all_philos_done;
	int					num_philos_done_eating;
	long long			start_time;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		data_mutex;
}						t_data;

/* Initialization */
int						init_data(t_data *data, int argc, char **argv);
int						init_philos(t_data *data);
int						init_mutexes(t_data *data);

/* Philosopher Actions & Routines */
void					*philosopher_routine(void *arg);
void					*monitor_routine(void *arg);
void					precise_sleep(long long duration, t_data *data);
void					philo_eat(t_philo *philo);

/* Thread Management */
void					start_threads(t_data *data);
void					join_threads(t_data *data);
void					cleanup(t_data *data);

/* Monitor Checks */
int						check_death(t_data *data);
int						check_all_meals_done(t_data *data);

/* Utils */
long long				get_time(void);
void					print_status(t_philo *philo, char *status);
int						ft_atoi(const char *str);

#endif
