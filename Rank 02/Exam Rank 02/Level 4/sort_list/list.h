#ifndef LIST_H
# define LIST_H

# include <stddef.h> //for NULL

typedef struct s_list
{
	int				data;
	struct s_list	*next;
}					t_list;

#endif
