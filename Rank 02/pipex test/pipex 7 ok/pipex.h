/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:57:42 by juwang            #+#    #+#             */
/*   Updated: 2025/07/12 22:46:17 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct s_pipex
{
	const char	*infile_name;
	const char	*outfile_name;
	char		*cmd1_str;
	char		*cmd2_str;
	char		**cmd1_args;
	char		**cmd2_args;
	int			infile_fd;
	int			outfile_fd;
	int			pipe_fds[2];
	pid_t		pid_cmd1;
	pid_t		pid_cmd2;
	char		**envp;
	char		*cmd_path_to_free;
}				t_pipex;

/* child_process_handler.c */
void			execute_first_command(t_pipex *data);
void			execute_second_command(t_pipex *data);

/* env_path_utils.c */
char			*find_env_var(char *envp[], const char *var_name);
char			*get_command_path(const char *cmd_name, char *envp[],
					t_pipex *data);

/* error_handling.c */
void			clean_up_resources(t_pipex *data);
void			print_command_error_and_exit(const char *cmd,
					const char *message, t_pipex *data);
void			handle_system_error(const char *message, t_pipex *data);

/* file_io_manager.c */
int				open_infile(const char *filename);
int				open_outfile(const char *filename);
void			create_pipe(int pipefd[2], t_pipex *data);

/* main_init_utils.c */
char			**parse_command_string(const char *cmd_str, t_pipex *data);
void			free_string_array(char **arr);
void			check_and_extract_args(t_pipex *data, int argc, char *argv[]);
void			parse_and_open_files(t_pipex *data);

/* main.c */
void			init_pipex_data(t_pipex *data, int argc, char *argv[],
					char *envp[]);
void			manage_child_processes(t_pipex *data);
void			parent_cleanup_and_wait(t_pipex *data);
int				main(int argc, char *argv[], char *envp[]);

#endif
