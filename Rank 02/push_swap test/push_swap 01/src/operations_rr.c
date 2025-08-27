/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:27:17 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 14:56:59 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h"

// op_rr 函数：同时执行 ra 和 rb
// 参数: a - 指向 A 栈的指针
//       b - 指向 B 栈的指针
//       print_op - 如果为 true，则打印操作指令 "rr\n"
void	op_rr(t_stack *a, t_stack *b, bool print_op)
{
	// 调用 op_ra 和 op_rb，但将它们的 print_op 设为 false，避免重复打印
	op_ra(a, false); // 不打印 "ra"
	op_rb(b, false); // 不打印 "rb"
	// 打印指令 (如果 print_op 为 true)
	if (print_op == true)
	{
		printf("rr\n"); // 最终请替换为 write(1, "rr\n", 3);
	}
}
