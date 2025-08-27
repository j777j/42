/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:04:14 by juwang            #+#    #+#             */
/*   Updated: 2025/07/12 22:20:17 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_command_string(const char *cmd_str, t_pipex *data)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd_str, ' ');
	if (!cmd_args || !cmd_args[0])
	{
		if (cmd_args)
			free(cmd_args);
		print_command_error_and_exit(cmd_str, "command not found", data);
		return (NULL);
	}
	return (cmd_args);
}

void	check_and_extract_args(t_pipex *data, int argc, char *argv[])
{
	if (argc != 5)
	{
		print_command_error_and_exit(NULL, "Incorrect number of arguments.",
			data);
	}
	data->infile_name = argv[1];
	data->cmd1_str = argv[2];
	data->cmd2_str = argv[3];
	data->outfile_name = argv[4];
}

void	parse_and_open_files(t_pipex *data)
{
	data->cmd1_args = parse_command_string(data->cmd1_str, data);
	data->cmd2_args = parse_command_string(data->cmd2_str, data);
	data->infile_fd = open_infile(data->infile_name);
	data->outfile_fd = open_outfile(data->outfile_name);
	create_pipe(data->pipe_fds, data);
}

void	free_string_array(char **cmd_args)
{
	size_t	i;

	if (!cmd_args)
		return ;
	i = 0;
	while (cmd_args[i])
	{
		free(cmd_args[i]);
		i++;
	}
	free(cmd_args);
}
