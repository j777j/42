/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/23 14:20:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Forward declarations
static void	execute_pipe_cmd(t_pipe_cmd *cmd, t_shell *shell, int in_pipe);
static void	execute_exec_cmd(t_exec_cmd *cmd, t_shell *shell, int in_pipe);
static void	execute_redir_cmd(t_redir_cmd *cmd, t_shell *shell, int in_pipe);
static int	handle_heredoc(t_redir_cmd *cmd);

void	execute_ast(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return ;
	// We are not in a pipe by default
	if (cmd->type == NODE_EXEC)
		execute_exec_cmd((t_exec_cmd *)cmd, shell, 0);
	else if (cmd->type == NODE_PIPE)
		execute_pipe_cmd((t_pipe_cmd *)cmd, shell, 0);
	else if (cmd->type == NODE_REDIR)
		execute_redir_cmd((t_redir_cmd *)cmd, shell, 0);
	else if (cmd->type == NODE_SEQ)
	{
		t_seq_cmd *scmd = (t_seq_cmd *)cmd;
		execute_ast(scmd->left, shell);
		execute_ast(scmd->right, shell);
	}
	else
		ft_putstr_fd("Error: Unknown node type\n", 2);
}

static void	execute_exec_cmd(t_exec_cmd *cmd, t_shell *shell, int in_pipe)
{
	pid_t	pid;
	char	*path;
	char	**envp_array;

	if (cmd->argv[0] == NULL)
		return ;
	// If it's a builtin that must run in the parent, and we are NOT in a pipe,
	// execute directly.
	if (is_parent_builtin(cmd->argv[0]) && !in_pipe)
	{
		dispatch_builtin(cmd, shell);
		return ;
	}
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (is_builtin(cmd->argv[0]))
		{
			dispatch_builtin(cmd, shell);
			exit(shell->exit_status);
		}
		path = find_command_path(cmd->argv[0], shell);
		if (!path)
		{
			ft_putstr_fd("minishell: command not found\n", 2);
			exit(127);
		}
		envp_array = env_list_to_array(shell->env_list);
		execve(path, cmd->argv, envp_array);
		// free path and envp_array on error
		exit(126);
	}
	waitpid(pid, &shell->exit_status, 0);
}

static void	execute_pipe_cmd(t_pipe_cmd *cmd, t_shell *shell, int in_pipe)
{
	int		p[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		status;

	(void)in_pipe;
	if (pipe(p) < 0)
	{
		perror("minishell: pipe");
		return ;
	}
	left_pid = fork();
	if (left_pid < 0)
	{
		perror("minishell: fork");
		return ;
	}
	if (left_pid == 0)
	{
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
		execute_ast(cmd->left, shell);
		exit(shell->exit_status);
	}
	right_pid = fork();
	if (right_pid < 0)
	{
		perror("minishell: fork");
		return ;
	}
	if (right_pid == 0)
	{
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		execute_ast(cmd->right, shell);
		exit(shell->exit_status);
	}
	close(p[0]);
	close(p[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}

static int	handle_heredoc(t_redir_cmd *cmd)
{
	char	*line;
	int		p[2];

	pipe(p);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, cmd->file, ft_strlen(cmd->file) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, p[1]);
		free(line);
	}
	close(p[1]);
	return (p[0]);
}

static void	execute_redir_cmd(t_redir_cmd *cmd, t_shell *shell, int in_pipe)
{
	pid_t	pid;
	int		fd;
	int		original_stdin;
	int		original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (cmd->mode == O_HEREDOC)
		fd = handle_heredoc(cmd);
	else
		fd = open(cmd->file, cmd->mode, 0644);
	if (fd < 0)
	{
		perror("minishell");
		shell->exit_status = 1;
		close(original_stdin);
		close(original_stdout);
		return;
	}
	dup2(fd, cmd->fd);
	close(fd);
	if (cmd->cmd->type == NODE_EXEC && is_parent_builtin(((t_exec_cmd *)cmd->cmd)->argv[0]) && !in_pipe)
		dispatch_builtin((t_exec_cmd *)cmd->cmd, shell);
	else
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			execute_ast(cmd->cmd, shell);
			exit(shell->exit_status);
		}
		waitpid(pid, &shell->exit_status, 0);
	}
	if (cmd->fd == STDIN_FILENO)
		dup2(original_stdin, STDIN_FILENO);
	else
		dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}
