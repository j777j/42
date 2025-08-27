/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:20:49 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 16:55:59 by juwang           ###   ########.fr       */
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
** join_path_and_cmd
** 拼接目录路径和命令名，形成完整的可执行路径。
** 例如：/bin + ls -> /bin/ls
** @param dir 命令所在的目录路径。
** @param cmd 命令的名称。
** @return char* 完整的路径字符串，需要调用者释放；失败返回NULL。
*/
char	*join_path_and_cmd(const char *dir, const char *cmd)
{
	char	*full_path;
	size_t	dir_len;
	size_t	cmd_len;

	dir_len = strlen(dir);
	cmd_len = strlen(cmd);
	full_path = (char *)malloc(sizeof(char) * (dir_len + cmd_len + 2));
	if (!full_path)
		return (NULL);
	memcpy(full_path, dir, dir_len);
	full_path[dir_len] = '/';
	memcpy(full_path + dir_len + 1, cmd, cmd_len);
	full_path[dir_len + cmd_len + 1] = '\0';
	return (full_path);
}

/*
** check_and_extract_args
** 辅助函数：检查命令行参数数量并提取文件名和命令字符串。
** @param data 指向 t_pipex 结构体的指针。
** @param argc 命令行参数计数。
** @param argv 命令行参数数组。
** @return void。
*/
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

/*
** parse_and_open_files
** 辅助函数：解析命令字符串并打开输入输出文件。
** @param data 指向 t_pipex 结构体的指针。
** @return void。
*/
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
}
