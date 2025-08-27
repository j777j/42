/*
Assignment name  : sort_list
Expected files   : sort_list.c
Allowed functions:
--------------------------------------------------------------------------------

Write the following functions:

t_list	*sort_list(t_list* lst, int (*cmp)(int, int));

This function must sort the list given as a parameter, using the function
pointer cmp to select the order to apply, and returns a pointer to the
first element of the sorted list.

Duplications must remain.

Inputs will always be consistent.

You must use the type t_list described in the file list.h
that is provided to you. You must include that file
(#include "list.h"), but you must not turn it in. We will use our own
to compile your assignment.

Functions passed as cmp will always return a value different from
0 if a and b are in the right order, 0 otherwise.

For example, the following function used as cmp will sort the list
in ascending order:

int	ascending(int a, int b)
{
	return (a <= b);
}
*/

#include "list.h"
#include "unistd.h"

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	int		tmp;
	t_list	*head;

	head = lst;
	while (lst != NULL && lst->next != NULL)
	{
		if ((*cmp)(lst->data, lst->next->data) == 0)
		{
			tmp = lst->data;
			lst->data = lst->next->data;
			lst->next->data = tmp;
			lst = head;
		}
		else
			lst = lst->next;
	}
	return (head);
}

// #include "list.h"

// void	ft_swap(int *a, int *b)
// {
// 	int	tmp;

// 	tmp = *a;
// 	*a = *b;
// 	*b = tmp;
// }

// t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
// {
// 	t_list	*current;
// 	int		sorted;

// 	sorted = 0;
// 	while (sorted == 0)
// 	{
// 		sorted = 1;
// 		current = lst;
// 		while (current != 0 && current->next != 0)
// 		{
// 			if (cmp(current->data, current->next->data) == 0)
// 			{
// 				ft_swap(&(current->data), &(current->next->data));
// 				sorted = 0;
// 			}
// 			current = current->next;
// 		}
// 	}
// 	return (lst);
// }
