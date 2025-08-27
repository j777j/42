/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:59:26 by juwang            #+#    #+#             */
/*   Updated: 2025/07/06 15:59:33 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_and_extract_args(t_pipex *data, int argc, char *argv[])
{
	if (argc != 5)
	{
		printf("Usage: ./pipex infile command1 command2 outfile\n");
		print_custom_error_and_exit("Incorrect number of arguments.");
	}
	data->infile_name = argv[1];
	data->cmd1_str = argv[2];
	data->cmd2_str = argv[3];
	data->outfile_name = argv[4];
}

static void	parse_and_open_files(t_pipex *data)
{
	data->cmd1_args = parse_command_string(data->cmd1_str);
	if (!data->cmd1_args)
		print_custom_error_and_exit("Failed to parse command 1.");
	data->cmd2_args = parse_command_string(data->cmd2_str);
	if (!data->cmd2_args)
	{
		free_command_args(data->cmd1_args);
		print_custom_error_and_exit("Failed to parse command 2.");
	}
	data->infile_fd = open_infile(data->infile_name);
	data->outfile_fd = open_outfile(data->outfile_name);
	create_pipe(data->pipe_fds);
	printf("Input file FD: %d\n", data->infile_fd);
	printf("Output file FD: %d\n", data->outfile_fd);
	printf("Pipe read end FD: %d\n", data->pipe_fds[0]);
	printf("Pipe write end FD: %d\n", data->pipe_fds[1]);
	fflush(stdout);
}

void	init_pipex_data(t_pipex *data, int argc, char *argv[], char *envp[])
{
	data->envp = envp;
	check_and_extract_args(data, argc, argv);
	parse_and_open_files(data);
}
