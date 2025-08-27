/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:18:25 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 17:43:26 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" // 包含项目主头文件

/*
** print_custom_error_and_exit
** 该函数处理应用程序的逻辑错误。
** 它会向标准错误流 (stderr) 打印一条自定义的错误信息，然后终止程序。
** 用于非系统调用引发的错误（例如：参数数量不正确）。
** @param message 要显示的错误信息字符串。
** @return void (不返回，因为它会退出程序)。
*/
void	print_custom_error_and_exit(const char *message)
{
	fprintf(stderr, "Error: %s\n", message);
	exit(EXIT_FAILURE);
}

/*
** handle_system_error
** 该函数处理系统调用错误。
** 它会使用 perror 来打印基于 errno 的系统错误描述，并带有一个自定义的前缀信息。
** 用于源自失败的系统调用（例如：文件未找到、权限不足）的错误。
** @param message 系统错误的自定义前缀信息。
** @return void (不返回，因为它会退出程序)。
*/
void	handle_system_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

/*
 * init_cmd_args_array
 * 辅助函数：初始化命令参数数组。
 * 它计算参数数量，分配 char** 数组的内存，并处理内存分配失败的情况。
 * @param cmd_str 原始命令字符串。
 * @param num_args 指向参数数量的指针。
 * @return char** 分配好的命令参数数组，失败则退出程序。
 */
char	**init_cmd_args_array(const char *cmd_str, size_t *num_args)
{
	char	**cmd_args;

	if (!cmd_str)
		return (NULL);
	*num_args = count_splits(cmd_str, ' ');
	cmd_args = (char **)malloc(sizeof(char *) * (*num_args + 1));
	if (!cmd_args)
	{
		handle_system_error("Failed to allocate memory for command arguments");
		return (NULL);
	}
	return (cmd_args);
}
