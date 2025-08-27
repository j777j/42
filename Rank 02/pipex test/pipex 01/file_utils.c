/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:20:49 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 13:20:59 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" // 包含项目主头文件

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

	fd = open(filename, O_RDONLY); // 以只读模式打开文件
	if (fd == -1)                  // 检查是否打开失败
	{
		handle_system_error("Error opening input file"); // 处理系统错误并退出
	}
	return (fd); // 返回文件描述符
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
	int fd;

	// O_WRONLY: 只写模式
	// O_CREAT: 如果文件不存在则创建
	// O_TRUNC: 如果文件存在且以写入模式打开，则将其内容截断为0长度
	// 0644: 新文件的权限（用户读写，组用户和其他用户只读）
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) // 检查是否打开失败
	{
		handle_system_error("Error opening output file"); // 处理系统错误并退出
	}
	return (fd); // 返回文件描述符
}
