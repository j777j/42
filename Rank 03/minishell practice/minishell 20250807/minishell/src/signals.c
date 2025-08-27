#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	main_sigint_handler(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	child_sigint_handler(int sig)
{
	(void)sig;
	ft_printf("\n");
}

static void	child_sigquit_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	setup_signals(int mode)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	if (mode == PARENT_PROMPT)
	{
		sa_int.sa_handler = main_sigint_handler;
		sa_quit.sa_handler = SIG_IGN;
	}
	else // CHILD_EXEC
	{
		sa_int.sa_handler = child_sigint_handler;
		sa_quit.sa_handler = child_sigquit_handler;
	}
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
