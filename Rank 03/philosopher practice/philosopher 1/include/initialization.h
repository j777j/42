#ifndef INITIALIZATION_H
# define INITIALIZATION_H

# include "structs.h"
# include "philosopher.h"

int	init_data(t_data *data, int argc, char **argv);
int	init_philos(t_data *data);
int	init_mutexes(t_data *data);

#endif
