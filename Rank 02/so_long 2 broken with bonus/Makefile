# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/06 12:00:00 by juwang            #+#    #+#              #
#    Updated: 2025/07/18 10:42:16 by juwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- 项目名称 ---
NAME = so_long

# --- 编译器和标志 ---
CC = clang
# 增加 -I minilibx 来包含 mlx.h
# 你的 so_long.h 已经包含了 mylibft 的头文件，所以 -I mylibft 仍然需要
CFLAGS = -Wall -Wextra -Werror -I includes -I mylibft -I minilibx

# --- 链接器标志 ---
# 链接你自己的 mylibft 库
LIBFT_FLAGS = -Lmylibft -l:mylibft.a# 通常库编译出来叫 libft.a，所以用 -lft

# 链接 MiniLibX 库 (根据你的操作系统选择)
# macOS:
#MLX_FLAGS = -Lminilibx -lmlx -framework OpenGL -framework AppKit
# Linux:
MLX_FLAGS = -Lminilibx -lmlx -lXext -lX11

# 合并所有链接标志
LDFLAGS = $(LIBFT_FLAGS) $(MLX_FLAGS)

# --- 库目录 ---
LIBFT_DIR = mylibft
LIBFT = $(LIBFT_DIR)/libft.a

# --- 源文件 ---
# VPATH 告诉 make 在哪里寻找源文件
VPATH = src

# 在这里列出你 so_long 项目的所有 .c 文件
SRCS =  main.c \
        init.c \
        map.c \
        map_utils.c \
        path.c \
        controls.c \
        render.c \
        exit.c \
		game.c \
		enemy.c

# --- 自动生成目标文件列表 ---
OBJS = $(SRCS:.c=.o)

# --- Makefile 规则 ---

# 默认规则
all: $(NAME)

# 链接生成最终的可执行文件
# 依赖于所有 .o 文件和你的 libft.a
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

# 编译 libft 库的规则
# 如果 libft.a 不存在，会自动进入 mylibft 目录执行 make
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# 将 .c 文件编译成 .o 文件的通用规则
# $< 代表依赖项中的第一个 (即 .c 文件)
# $@ 代表目标 (即 .o 文件)
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# 清理规则
clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

# 完全清理规则
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# 重新编译规则
re: fclean all

# 伪目标，防止和文件名冲突
.PHONY: all clean fclean re
