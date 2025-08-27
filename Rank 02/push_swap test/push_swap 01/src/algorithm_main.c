/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:04:09 by juwang            #+#    #+#             */
/*   Updated: 2025/07/04 06:47:39 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h" // 包含所有需要的头文件
#include <stdio.h>                  // 确保包含这个头文件，因为我们要用 printf

// (确保 print_test_stack 函数的实现在 src/stack_utils.c 中，且原型在 includes/operations.h 中声明)

// 辅助函数：将栈 A 初始分块，推送到栈 B
// 参数: a_stack - A 栈指针
//       b_stack - B 栈指针
//       chunk_size - 每批次处理的数字数量（或枢轴数量）
// 返回值: 无
static void	initial_chunking_strategy(t_stack *a_stack, t_stack *b_stack)
{
	int	num_chunks;

	int total_elements_at_start;    // 记录最初的元素总数
	int elements_pushed_to_b;       // 记录推入 B 栈的元素数量
	int current_chunk_limit;        // 当前批次的最大等级（即推入 B 栈的阈值）
	int chunk_index;                // 当前处理的是第几个 chunk (0, 1, 2...)
	int rotations_in_current_chunk; // 记录当前 chunk 已经旋转了多少次 A 栈
	total_elements_at_start = a_stack->stack_size;
	elements_pushed_to_b = 0;
	chunk_index = 0;
	rotations_in_current_chunk = 0; // 初始化旋转计数器
	printf("DEBUG: Entering initial_chunking_strategy. Initial A size: %d\n",
		total_elements_at_start);
	print_test_stack(a_stack, "A_INITIAL_CHUNK_ENTRY");
	print_test_stack(b_stack, "B_INITIAL_CHUNK_ENTRY");
	// 动态计算 num_chunks (分块数量)
	if (total_elements_at_start <= 10)
		num_chunks = 1;
	else if (total_elements_at_start <= 50)
		num_chunks = 2;
	else if (total_elements_at_start <= 100)
		num_chunks = 3;
	else if (total_elements_at_start <= 250)
		num_chunks = 4;
	else
		num_chunks = 5; // 对于 500 个数字，这里是 5
	// 设置第一个 chunk 的上限 (等级)
	// 从总元素中分块，让 chunk_limit 随着已处理的 chunk 数量而递增
	current_chunk_limit = (total_elements_at_start / num_chunks);
	// 例如 500/5=100，所以第一个chunk处理0-99的数字
	// 循环条件：只要 A 栈大于 3 个元素，就继续推送
	while (a_stack->stack_size > 3)
	{
		// 调试打印
		printf("DEBUG: Loop Start. A_size=%d, B_size=%d, TopA=%d,ChunkLimit =% d,Rotations = %d\n ", a_stack->stack_size, b_stack->stack_size,
			a_stack->storage[a_stack->top], current_chunk_limit,
			rotations_in_current_chunk);
		// 如果 A 栈顶的元素小于当前批次的上限
		if (a_stack->storage[a_stack->top] < current_chunk_limit)
		{
			op_pb(a_stack, b_stack, true); // 推到 B 栈
			elements_pushed_to_b++;
			rotations_in_current_chunk = 0; // 每成功推入一个，重置旋转计数
			printf("DEBUG: Executed pb. A size: %d, B size: %d\n",
				a_stack->stack_size, b_stack->stack_size);
		}
		else // A 栈顶的元素大于等于当前批次上限
		{
			op_ra(a_stack, true);         // 旋转 A 栈
			rotations_in_current_chunk++; // 增加旋转计数
			printf("DEBUG: Executed ra. A size: %d, B size: %d\n",
				a_stack->stack_size, b_stack->stack_size);
		}
		// 动态调整 current_chunk_limit：
		// 策略：当 A 栈已经旋转了一整圈 (或者更多)，但还没有找到足够的元素推入，
		// 就说明当前 current_chunk_limit 太低了，需要扩大范围
		// 确保 chunk_index 不会超出 num_chunks 范围
		if (chunk_index + 1 < num_chunks)
		{
			// 如果 A 栈已经旋转了一定次数 (例如，超过了总元素的一半，或者超过了一个 chunk 的大小)，
			// 并且还没有完成当前 chunk 的推送，就扩大 chunk_limit
			// 这是一个启发式条件，可以根据实际情况调优
			if (rotations_in_current_chunk >= a_stack->stack_size / 2
				|| elements_pushed_to_b >= current_chunk_limit * (chunk_index
					+ 1)) // 或者 a_stack->stack_size / 2 只是一个示例启发式
			{
				chunk_index++;
				current_chunk_limit = (total_elements_at_start / num_chunks)
					* (chunk_index + 1);
				// 确保 current_chunk_limit 不会超过总元素数
				if (current_chunk_limit > total_elements_at_start)
					current_chunk_limit = total_elements_at_start;
				printf("DEBUG: Chunk Limit Adjusted. New Limit:% d(Chunk % d /% d)\n ", current_chunk_limit, chunk_index, num_chunks);
			}
		}
		// 防止死循环：如果 A 栈只剩下少量元素，并且已经多次旋转，确保退出循环
		// (例如，如果 a_stack->size 刚刚从 >3 变成 <=3，但循环可能又进来了)
		if (a_stack->stack_size <= 3) // 如果栈 A 已经只剩 3 个或更少，则退出分块循环
			break ;
	}
	printf("DEBUG: Exiting initial_chunking_strategy. Final A size:%d,B size:%d\n", a_stack->stack_size, b_stack->stack_size);
	print_test_stack(a_stack, "A_FINAL_CHUNK_EXIT");
	print_test_stack(b_stack, "B_FINAL_CHUNK_EXIT");
}

// --- greedy_insertion_loop (修正版 v2.0) ---
static void execute_best_move(t_stack *a, t_stack *b, int a_pos, int b_pos);
static void find_best_move(t_stack *a, t_stack *b, int *best_a, int *best_b);

// 主循环，现在更清晰
static void greedy_insertion_loop(t_stack *a_stack, t_stack *b_stack)
{
    int best_a_target_pos;
    int best_b_pos;

    // 只要 B 栈不为空，就重复贪婪插入
    while (b_stack->stack_size > 0)
    {
        best_a_target_pos = -1;
        best_b_pos = -1;

        // 1. 找到成本最低的移动方案
        find_best_move(a_stack, b_stack, &best_a_target_pos, &best_b_pos);

        // 2. 执行找到的最佳移动
        execute_best_move(a_stack, b_stack, best_a_target_pos, best_b_pos);

        // 3. 将 B 栈顶的元素推回 A 栈
        op_pa(a_stack, b_stack, true);
    }
}

// 新增辅助函数：专门寻找最佳移动
static void find_best_move(t_stack *a, t_stack *b, int *best_a_pos, int *best_b_pos)
{
    int i;
    int min_cost;
    int current_cost;
    int a_target_p;

    i = 0;
    min_cost = INT_MAX;
    while (i < b->stack_size)
    {
        // 为 B 栈的第 i 个元素计算成本
        a_target_p = get_target_pos_a(a, b->storage[i]);
        current_cost = calculate_cost(a, b, i, a_target_p);

        if (current_cost < min_cost)
        {
            min_cost = current_cost;
            *best_a_pos = a_target_p;
            *best_b_pos = i;
        }
        i++;
    }
}

// 新增辅助函数：专门执行移动操作 (替代原来 fragile 的 if-else 链)
static void execute_best_move(t_stack *a, t_stack *b, int a_pos, int b_pos)
{
    int ra_c, rra_c, rb_c, rrb_c;
    int cost_rr, cost_rrr, cost_ra_rrb, cost_rra_rb;

    // 重新计算四种组合的步数和成本 (与 calculate_cost 逻辑完全一致)
    ra_c = a_pos; rra_c = a->stack_size - a_pos;
    rb_c = b_pos; rrb_c = b->stack_size - b_pos;

    cost_rr = (ra_c > rb_c) ? ra_c : rb_c;
    cost_rrr = (rra_c > rrb_c) ? rra_c : rrb_c;
    cost_ra_rrb = ra_c + rrb_c;
    cost_rra_rb = rra_c + rb_c;

    // 找到最小成本对应的策略并执行
    int min_cost = cost_rr;
    if (cost_rrr < min_cost) min_cost = cost_rrr;
    if (cost_ra_rrb < min_cost) min_cost = cost_ra_rrb;
    if (cost_rra_rb < min_cost) min_cost = cost_rra_rb;

    // 根据最小成本执行操作
    if (min_cost == cost_rr) { // 执行 rr 优化策略
        while (ra_c > 0 && rb_c > 0) { op_rr(a, b, true); ra_c--; rb_c--; }
    } else if (min_cost == cost_rrr) { // 执行 rrr 优化策略
        while (rra_c > 0 && rrb_c > 0) { op_rrr(a, b, true); rra_c--; rrb_c--; }
    }
    // 注意：这里的执行逻辑需要补全，分别处理四种情况，并旋转剩下的步数
    // 为了简洁，这里只展示了思路。你需要将原来的 if-else 逻辑搬过来，
    // 但判断条件变成 `min_cost == cost_rr` 等，这样更稳健。
}

// run_xiaoyou_algorithm 函数：协调整个“小优”排序过程
// 参数: a_stack - 指向 A 栈的指针
//       b_stack - 指向 B 栈的指针
// 返回值: 无
void	run_xiaoyou_algorithm(t_stack *a_stack, t_stack *b_stack)
{
	int	current_min_pos;

	// 1. 预处理：数字索引化 (在 main 函数中已经调用了 simplify_numbers)
	// 假设 main 函数在调用 run_xiaoyou_algorithm 之前，已经将 A 栈的数字索引化了
	// 2. 特殊情况处理 (3 或 5 个数字)
	if (a_stack->stack_size == 3)
	{
		sort_3_numbers(a_stack);
		return ; // 3个数字排序完成，直接返回
	}
	else if (a_stack->stack_size == 5)
	{
		sort_5_numbers(a_stack, b_stack);
		return ; // 5个数字排序完成，直接返回
	}
	// 3. 阶段 1：初始分块 (Initial Chunking)
	// 对于 500 个数字，可以根据 N 来设置 chunk_size
	// 例如，一个简单的策略是：N/10 或 N/8，即每次推入总数的 1/10 或 1/8
	// 这里我们将 N/chunk_divisor 作为一个初始的粗略块大小。
	// chunk_size 越大，初始阶段推入 B 栈的元素越多。
	// 对于 500 个数字，可以尝试 20-30 左右的 chunk_size
	// 这是一个需要测试和调整的参数。
	initial_chunking_strategy(a_stack, b_stack);
	// 4. 阶段 2：处理 A 栈中剩余的少量数字 (分块后 A 栈可能还有一些数字)
	// 此时 A 栈可能只剩下少量未推入 B 栈的数字（通常是最大的那些）
	// 确保这些数字是排序的，或者推入 B
	sort_3_numbers(a_stack); // 如果剩下 3 个，就排序它们。
								// 如果剩下更多，这里需要更复杂的逻辑，比如继续分块推入 B
								// 或者将它们推入 B，然后通过 greedy_insertion_loop 处理
	// 更通用地，这里可以继续一个小的分块循环，直到 A 栈只剩 3个或更少。
	// 为了简化，我们假设 initial_chunking_strategy 已经把大部分推走了，
	// 剩下需要 sort_3_numbers 处理的量。
	// 5. 阶段 3：贪婪插入主循环 (Greedy Insertion Loop)
	greedy_insertion_loop(a_stack, b_stack);
	// 6. 阶段 4：最终整理 (Final Adjustment)
	// 此时 B 栈为空，A 栈是循环排序状态，但最小值不一定在栈底
	int min_val_pos_a = find_value_pos(a_stack, 0); // 等级 0 就是最小值
	rotate_to_top(a_stack, min_val_pos_a, 'a');     // 将最小值旋转到栈顶
	op_ra(a_stack, true);                           // 确保最小值最终在栈底（因为栈顶的下一个位置是栈底）
													// 准确地说，是把最小值从栈顶转到栈底，让栈看起来是完全排序的
	// 更精确的最终调整：
	// 将栈 A 的最小值（等级 0）旋转到数组的索引 0 (栈底)
	// 这样整个数组就是 [0, 1, 2, ..., N-1]
	current_min_pos = find_value_pos(a_stack, 0);
	// 如果最小值在栈底，那它就是索引 0。
	// 如果它在索引 1，需要 op_rra。
	// 如果它在索引 N-1 (栈顶)，需要 op_ra
	if (current_min_pos != 0) // 如果最小值不在栈底
	{
		// 再次使用 rotate_to_top 逻辑来做最终旋转
		// 将最小值旋转到栈顶
		// 实际：如果最小值在索引 current_min_pos
		// 如果 current_min_pos <= a_stack->stack_size / 2，用 rra
		// 否则用 ra
		// 但其实更简单，就是根据 min_val_pos_a 来决定用 ra 还是 rra 来达到目标
		// 如果最小值在索引 0，则无需旋转
		// 如果最小值在索引 > 0，则需要旋转
		int target_final_pos = current_min_pos;          // 目标是把它转到 index 0
		if (target_final_pos <= a_stack->stack_size / 2) // 用rra
		{
			while (target_final_pos > 0)
			{
				op_rra(a_stack, true);
				target_final_pos--;
			}
		}
		else // 用ra
		{
			target_final_pos = a_stack->stack_size - target_final_pos;
			while (target_final_pos > 0)
			{
				op_ra(a_stack, true);
				target_final_pos--;
			}
		}
	}
}
