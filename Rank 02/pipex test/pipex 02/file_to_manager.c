/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:55:07 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 17:55:20 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** open_infile
** 以只读模式打开指定的文件。
** 如果文件无法打开，则以错误信息终止程序。
** @param filename 输入文件的路径。
** @return int 已打开输入文件的文件描述符。
*/
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

/*
** open_outfile
** 以只写模式打开或创建指定的文件。
** 如果文件已存在，其内容将被截断（清空）。
** 如果文件无法打开/创建，则以错误信息终止程序。
** @param filename 输出文件的路径。
** @return int 已打开输出文件的文件描述符。
*/
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

/*
** create_pipe
** 创建一个匿名管道，并将其读写端文件描述符存储在提供的数组中。
** 如果管道创建失败，则会调用错误处理函数并退出程序。
** @param pipefd 存储管道读写端文件描述符的整数数组
** (pipefd[0]为读端，pipefd[1]为写端)。
** @return void。
*/
void	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		handle_system_error("Error creating pipe");
	}
}
