/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:12:01 by juwang            #+#    #+#             */
/*   Updated: 2025/07/26 17:30:09 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POWERSET_H
# define POWERSET_H

# include <stdio.h>
# include <stdlib.h>

typedef struct s_subset
{
	int				*elements;
	int				size;
	struct s_subset	*next;
}					t_subset;

// Core functions
void				find_subsets(int *arr, int n, int target,
						t_subset **result);
void				backtrack(int *arr, int n, int target, int index,
						int *current, int current_size, t_subset **result);

// Subset management
t_subset			*create_subset(int *elements, int size);
void				add_subset(t_subset **head, int *elements, int size);
void				print_and_free_subsets(t_subset *head);

// Utility functions
int					parse_arguments(int argc, char **argv, int **numbers);
void				error_exit(void);

#endif

#ifndef POWERSET_H
# define POWERSET_H

# include <stdio.h> // For printf
# include <stdlib.h> // For malloc, free, atoi

// 这是一个独立的可执行程序，没有需要向外暴露的公共函数。
// 所有辅助函数都应在 .c 文件中声明为 static。
// 因此，此头文件无需包含任何函数原型。

#endif
