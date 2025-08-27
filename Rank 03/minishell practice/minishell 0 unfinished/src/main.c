/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/22 12:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** The main loop of the shell.
*/
static void	shell_loop(t_shell *shell)
{
	char	*line;
	t_token	*tokens;
	t_token	*tokens_head;
	t_cmd	*cmd;

	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		if (*line)
		{
			add_history(line);
			tokens = lexer(line, shell);
			tokens_head = tokens;
			cmd = parse_command(&tokens, shell);
			if (cmd)
			{
				execute_ast(cmd, shell);
				free_ast(cmd);
			}
			free_tokens(tokens_head);
		}
		free(line);
	}
}

/*
** The entry point of the minishell program.
*/
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	setup_signals(PARENT_PROMPT);
	init_shell(&shell, envp);
	shell_loop(&shell);
	// TODO: free shell.env_list
	return (shell.exit_status);
}
