/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/11 14:30:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static int	is_numeric(const char *s)
{
	if (*s == '+' || *s == '-')
		s++;
	if (!*s)
		return (0);

	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

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

	// Case 1: "exit" with too many arguments.
	// Bash prints an error, sets status to 1, and does NOT exit.
	// It also does not print the initial "exit" message.
	if (args[1] && is_numeric(args[1]) && args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_status = 1;
		return ;
	}

	// If we are in an interactive shell, print "exit" before exiting.
	// The tester runs in non-interactive mode, so this won't be printed.
	if (isatty(STDIN_FILENO))
	{
		ft_putendl_fd("exit", 2);
	}

	// Case 2: "exit" with no arguments. Exits with the last status.
	if (!args[1])
	{
		exit(shell->exit_status);
	}

	// Case 3: Argument is not numeric. Print error and exit with 2.
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	
	// Case 4: "exit" with one numeric argument.
	// This case is now handled after the "too many arguments" check.
	if (args[1] && !args[2])
	{
		exit_code = ft_atoi(args[1]);
		exit(exit_code % 256);
	}
	
	// Fallback, should not be reached with the logic above.
	exit(shell->exit_status);
}
