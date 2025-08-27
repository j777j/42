/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_ss.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:27:28 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 14:56:55 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h"

// op_ss 函数：同时执行 sa 和 sb
// 参数: a - 指向 A 栈的指针
//       b - 指向 B 栈的指针
//       print_op - 如果为 true，则打印操作指令 "ss\n"
void	op_ss(t_stack *a, t_stack *b, bool print_op)
{
	// 调用 op_sa 和 op_sb，但将它们的 print_op 设为 false，避免重复打印
	op_sa(a, false); // 不打印 "sa"
	op_sb(b, false); // 不打印 "sb"
	// 打印指令 (如果 print_op 为 true)
	if (print_op == true)
	{
		printf("ss\n"); // 最终请替换为 write(1, "ss\n", 3);
	}
}
