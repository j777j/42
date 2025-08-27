/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rrr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:27:23 by juwang            #+#    #+#             */
/*   Updated: 2025/07/03 14:56:52 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h"

// op_rrr 函数：同时执行 rra 和 rrb
// 参数: a - 指向 A 栈的指针
//       b - 指向 B 栈的指针
//       print_op - 如果为 true，则打印操作指令 "rrr\n"
void	op_rrr(t_stack *a, t_stack *b, bool print_op)
{
	// 调用 op_rra 和 op_rrb，但将它们的 print_op 设为 false，避免重复打印
	op_rra(a, false); // 不打印 "rra"
	op_rrb(b, false); // 不打印 "rrb"
	// 打印指令 (如果 print_op 为 true)
	if (print_op == true)
	{
		printf("rrr\n"); // 最终请替换为 write(1, "rrr\n", 3);
	}
}
