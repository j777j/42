/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:01:27 by juwang            #+#    #+#             */
/*   Updated: 2025/07/06 17:01:40 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(const char *filename, t_pipex *data)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		handle_system_error("Error opening input file", data);
	}
	return (fd);
}

int	open_outfile(const char *filename, t_pipex *data)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		handle_system_error("Error opening output file", data);
	}
	return (fd);
}

void	create_pipe(int pipefd[2], t_pipex *data)
{
	if (pipe(pipefd) == -1)
	{
		handle_system_error("Error creating pipe", data);
	}
}
