/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:18:25 by juwang            #+#    #+#             */
/*   Updated: 2025/07/05 13:19:53 by juwang           ###   ########.fr       */
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
	fprintf(stderr, "Error: %s\n", message); // 打印到标准错误流
	exit(EXIT_FAILURE);                      // 以失败状态退出程序
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
	perror(message);    // perror 会自动附加系统错误详情（例如："No such file or directory"）
	exit(EXIT_FAILURE); // 以失败状态退出程序
}
