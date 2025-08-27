/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:00:19 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:56:40 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int		is_numeric(const char *s);
void	handle_numeric_arg_required(char *arg);
void	handle_too_many_args(t_shell *shell);

/*
** ft_exit
** Implements the exit command, mimicking bash's behavior.
** - Prints "exit" only in interactive mode when the shell is about to exit.
** - Handles "too many arguments" error without exiting.
** - Handles "numeric argument required" error by exiting with status 2.
*/
void	ft_exit(char **args, t_shell *shell)
{
	int	exit_code;

	if (args[1] && is_numeric(args[1]) && args[2])
	{
		handle_too_many_args(shell);
		return ;
	}
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 2);
	if (!args[1])
		exit(shell->exit_status);
	if (!is_numeric(args[1]))
		handle_numeric_arg_required(args[1]);
	if (args[1] && !args[2])
	{
		exit_code = ft_atoi(args[1]);
		exit(exit_code % 256);
	}
	exit(shell->exit_status);
}
