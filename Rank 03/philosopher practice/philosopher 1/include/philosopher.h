#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# include "structs.h"
# include "philo_actions.h"
# include "monitor_checks.h"
# include "initialization.h"

// Function prototypes
long long	get_time(void);
void		print_status(t_philo *philo, char *status);
void		*philosopher_routine(void *arg);
void		start_threads(t_data *data);
void		join_threads(t_data *data);
void		cleanup(t_data *data);
int			ft_atoi(const char *str);
void		*monitor_routine(void *arg);

#endif
