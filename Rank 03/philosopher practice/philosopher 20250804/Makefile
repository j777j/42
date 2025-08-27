# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/31 15:23:12 by juwang            #+#    #+#              #
#    Updated: 2025/08/02 23:46:39 by juwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 可执行文件名
NAME = philo

# 编译器和编译选项
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g

# 目录定义
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# 源文件 (.c)
# 👇 *** 确保你所有的 .c 文件都在这里列出 *** 👇
SRCS =	main.c \
		initialization.c \
		philosopher.c \
		monitor.c \
		threads.c \
		utils.c

# 为源文件添加 src/ 前缀
SRC_FILES = $(addprefix $(SRC_DIR)/, $(SRCS))

# 目标文件 (.o)
# 这会自动生成一个类似 obj/main.o obj/initialization.o ... 的列表
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# 主要规则
all: $(NAME)

# 链接规则
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $(NAME) $(OBJS)

# 编译规则
# 这个规则告诉 make 如何从 src/ 目录下的 .c 文件生成一个 obj/ 目录下的 .o 文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# 清理规则
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# 伪目标
.PHONY: all clean fclean re
