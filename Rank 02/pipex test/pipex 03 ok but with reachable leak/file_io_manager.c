/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:46:46 by juwang            #+#    #+#             */
/*   Updated: 2025/07/06 15:46:48 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		handle_system_error("Error opening input file");
	}
	return (fd);
}

int	open_outfile(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		handle_system_error("Error opening output file");
	}
	return (fd);
}

void	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		handle_system_error("Error creating pipe");
	}
}
