# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/06 16:01:47 by juwang            #+#    #+#              #
#    Updated: 2025/07/06 16:01:55 by juwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 程序名称
NAME = pipex

# 编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -Wextra -Werror

# 头文件目录
HEADERS = -I.

# 源文件列表
SRCS = \
	main.c \
	error_handling.c \
	file_io_manager.c \
	string_base_utils.c \
	string_utils.c \
	env_path_utils.c \
	command_parser.c \
	child_process_handler.c \
	main_init_utils.c

# 对象文件列表
OBJS = $(SRCS:.c=.o)

# 默认规则：编译所有对象文件并链接生成可执行文件
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME)

# 编译 .c 文件生成 .o 文件
%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

# 清理对象文件
clean:
	rm -f $(OBJS)

# 清理所有生成的文件 (对象文件和可执行文件)
fclean: clean
	rm -f $(NAME)

# 重新编译 (fclean 然后 all)
re: fclean all

# 伪目标声明，避免与同名文件冲突
.PHONY: all clean fclean re
