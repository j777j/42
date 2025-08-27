# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/03 15:22:28 by juwang            #+#    #+#              #
#    Updated: 2025/07/04 08:24:38 by juwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# --- Compiler and Flags ---
# CC: 使用 clang
# CFLAGS: 编译标志
# -Wall -Wextra -Werror: 开启所有常用警告，并将它们视为错误，保证代码质量
# -I includes: 告诉编译器去 "includes" 文件夹里寻找头文件
CC = clang
CFLAGS = -Wall -Wextra -Werror -I includes

# --- Executable Name ---
# NAME: 我们最终生成的可执行文件的名字
NAME = push_swap

# --- Source Files ---
# SRCS: 列出我们所有的 .c 源文件
SRCS = src/main.c \
       src/init.c \
       src/parse.c \
       src/setup.c \
       src/simplify.c \
       src/algorithm.c \
       src/general_sort.c \
       src/chunking.c \
       src/greedy.c \
       src/execute_move.c \
       src/final_alignment.c \
       src/sort_small.c \
       src/utils.c \
       src/operations/swap.c \
       src/operations/push.c \
       src/operations/rotate.c \
       src/operations/reverse_rotate.c

# --- Object Files ---
# OBJS: 根据源文件自动生成对应的 .o 目标文件名
OBJS = $(SRCS:.c=.o)

# --- Rules ---
# all: 默认规则，当你在终端输入 `make` 时会执行
# 它依赖于 $(NAME)，也就是我们的可执行文件
all: $(NAME)

# $(NAME): 生成可执行文件的规则
# 它依赖于所有的 .o 文件
# $@: 代表规则的目标 (这里是 push_swap)
# $^: 代表规则的所有依赖 (这里是所有的 .o 文件)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# %.o: %.c: 一个通用规则，告诉 make 如何从任意 .c 文件生成 .o 文件
# $<: 代表规则的第一个依赖 (这里是单个 .c 文件)
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# clean: 清理规则，用于删除所有的 .o 文件
clean:
	rm -f $(OBJS)

# fclean: 彻底清理规则，删除 .o 文件和可执行文件
fclean: clean
	rm -f $(NAME)

# re: 重新编译规则，先彻底清理，然后重新编译
re: fclean all

# .PHONY: 声明这些是“伪目标”，它们不代表真实的文件名
.PHONY: all clean fclean re
