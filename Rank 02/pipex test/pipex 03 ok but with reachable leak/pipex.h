/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:45:59 by juwang            #+#    #+#             */
/*   Updated: 2025/07/06 15:55:39 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
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
}				t_pipex;

/* error_handling.c */
void			print_custom_error_and_exit(const char *message);
void			handle_system_error(const char *message);

/* file_io_manager.c */
int				open_infile(const char *filename);
int				open_outfile(const char *filename);
void			create_pipe(int pipefd[2]);

/* string_base_utils.c */
size_t			count_words_split(const char *s, char c);
size_t			get_substring_len_split(const char *s, char c);
int				alloc_copy_substring(char **arr, const char *s, size_t len,
					size_t i);

/* string_utils.c */
char			**ft_split(const char *s, char c);
void			free_string_array(char **arr);
char			*string_join(const char *s1, const char *s2);
void			free_command_args(char **cmd_args);

/* env_path_utils.c */
char			*find_env_var(char *envp[], const char *var_name);
char			*get_command_path(const char *cmd_name, char *envp[]);

/* command_parser.c */
char			**parse_command_string(const char *cmd_str);
/* free_command_args 移走了 */

/* child_process_handler.c */
void			execute_first_command(int infile_fd, int pipe_fds[2],
					char *cmd_args[], char *envp[]);
void			execute_second_command(int outfile_fd, int pipe_fds[2],
					char *cmd_args[], char *envp[]);

/* main_init_utils.c */
void			init_pipex_data(t_pipex *data, int argc, char *argv[],
					char *envp[]);

/* main.c */
void			manage_child_processes(t_pipex *data);
void			parent_cleanup_and_wait(t_pipex *data);

#endif
