/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:18:13 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 13:45:44 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// --- 标准库头文件 ---
# include <fcntl.h>    // 包含文件控制标志，如 O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC
# include <stdio.h>    // 包含标准输入输出函数，如 printf, fprintf, perror
# include <stdlib.h>   // 包含通用工具函数，如 exit
# include <string.h>   // 包含字符串处理函数，如 strlen, strcpy, strncmp, strchr
# include <sys/stat.h> // 包含文件权限相关类型，如 mode_t
# include <unistd.h>   // 包含POSIX系统调用，如 fork, pipe, execve, close, dup2, access

// --- 错误处理函数 (在 error_utils.c 中实现) ---
void	print_custom_error_and_exit(const char *message);
void	handle_system_error(const char *message);

// --- 文件工具函数 (在 file_utils.c 中实现) ---
int		open_infile(const char *filename);
int		open_outfile(const char *filename);

// --- 管道工具函数 (在 pipe_utils.c 中实现) ---
void	create_pipe(int pipefd[2]);

// --- 路径查找函数 (在 path_finder.c 中实现) ---
char	*get_cmd_path(const char *cmd_name, char *envp[]);

// --- 命令解析函数 (在 cmd_parser.c 中实现) ---
char	**parse_command_string(const char *cmd_str);
void	free_command_args(char **cmd_args);

// --- 子进程管理函数 (在 child_process.c 中实现) ---
void	execute_first_command(int infile_fd, int pipe_fds[2], char *cmd_args[],
			char *envp[]);
void	execute_second_command(int outfile_fd, int pipe_fds[2],
			char *cmd_args[], char *envp[]);

#endif
