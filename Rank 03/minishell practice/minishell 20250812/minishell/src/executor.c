/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/31 11:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

static void	execute_pipe_cmd(t_pipe_cmd *cmd, t_shell *shell);
static void	execute_simple_command(t_cmd *cmd, t_shell *shell, int in_pipe);
static int	apply_redirections(t_list *redir_list, t_shell *shell);
static void	execute_in_child(t_exec_cmd *ecmd, t_shell *shell);
static int	handle_heredoc(t_redir_cmd *cmd);

void	execute_ast(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return ;
	if (cmd->type == NODE_PIPE)
		execute_pipe_cmd((t_pipe_cmd *)cmd, shell);
	else if (cmd->type == NODE_SEQ)
	{
		t_seq_cmd *scmd = (t_seq_cmd *)cmd;
		execute_ast(scmd->left, shell);
		execute_ast(scmd->right, shell);
	}
	else
		execute_simple_command(cmd, shell, 0);
}

static void	execute_simple_command(t_cmd *cmd, t_shell *shell, int in_pipe)
{
	t_list		*redir_list;
	t_exec_cmd	*ecmd;
	t_cmd		*current_cmd;
	pid_t		pid;
	int			fds[2];

	redir_list = NULL;
	current_cmd = cmd;
	while (current_cmd->type == NODE_REDIR)
	{
		ft_lstadd_front(&redir_list, ft_lstnew(current_cmd));
		current_cmd = ((t_redir_cmd *)current_cmd)->cmd;
	}
	ecmd = (t_exec_cmd *)current_cmd;
	expand_command_args(ecmd, shell);
	if (ecmd->argv[0] && is_parent_builtin(ecmd->argv[0]) && !in_pipe)
	{
		fds[0] = dup(STDIN_FILENO);
		fds[1] = dup(STDOUT_FILENO);
		if (apply_redirections(redir_list, shell))
			dispatch_builtin(ecmd, shell);
		dup2(fds[0], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			return ;
		if (pid == 0)
		{
			if (!apply_redirections(redir_list, shell))
				exit(shell->exit_status);
			execute_in_child(ecmd, shell);
		}
		waitpid(pid, &shell->exit_status, 0);
		if (WIFEXITED(shell->exit_status))
			shell->exit_status = WEXITSTATUS(shell->exit_status);
	}
	ft_lstclear(&redir_list, NULL);
}

static int	apply_redirections(t_list *redir_list, t_shell *shell)
{
	t_list		*current;
	t_redir_cmd	*redir;
	char		*expanded_file;
	int			fd;

	current = redir_list;
	while (current)
	{
		redir = (t_redir_cmd *)current->content;
		expanded_file = perform_expansion(redir->file, shell);
		if (redir->mode == O_HEREDOC)
			fd = handle_heredoc(redir);
		else
			fd = open(expanded_file, redir->mode, 0644);
		if (fd < 0)
		{
			perror(expanded_file);
			shell->exit_status = 1;
			free(expanded_file);
			return (0);
		}
		if (dup2(fd, redir->fd) == -1)
		{
			perror("dup2");
			close(fd);
			free(expanded_file);
			return (0);
		}
		close(fd);
		free(expanded_file);
		current = current->next;
	}
	return (1);
}

static void	execute_in_child(t_exec_cmd *cmd, t_shell *shell)
{
	char		*path;
	char		**envp_array;
	struct stat	statbuf;

	if (cmd->argv[0] == NULL)
		exit(0);
	if (is_builtin(cmd->argv[0]))
	{
		dispatch_builtin(cmd, shell);
		exit(shell->exit_status);
	}
	path = find_command_path(cmd->argv[0], shell);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (stat(path, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			free(path);
			exit(126);
		}
	}
	envp_array = env_list_to_array(shell->env_list);
	execve(path, cmd->argv, envp_array);
	int err = errno;
	ft_putstr_fd("minishell: ", 2);
	perror(path);
	free(path);
	if (err == EACCES)
		exit(126);
	exit(127);
}

static void	execute_pipe_cmd(t_pipe_cmd *cmd, t_shell *shell)
{
	int		p[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		status;

	if (pipe(p) < 0)
		return ;
	left_pid = fork();
	if (left_pid < 0)
		return ;
	if (left_pid == 0)
	{
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
		execute_simple_command(cmd->left, shell, 1);
		exit(shell->exit_status);
	}
	right_pid = fork();
	if (right_pid < 0)
		return ;
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
			if (line)
				free(line);
			break ;
		}
		ft_putendl_fd(line, p[1]);
		free(line);
	}
	close(p[1]);
	return (p[0]);
}
