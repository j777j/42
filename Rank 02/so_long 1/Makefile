# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/06 12:00:00 by juwang            #+#    #+#              #
#    Updated: 2025/07/06 12:00:00 by juwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCS = -I. -I./mylibft
LIBFT = ./mylibft/libft.a
MLX = ./minilibx/libmlx.a
LIBS = -L./mylibft -lft -L./minilibx -lmlx -lXext -lX11
RM = rm -f

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(INCS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	make -C ./mylibft

$(MLX):
	make -C ./minilibx

clean:
	make -C ./mylibft clean
	make -C ./minilibx clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	make -C ./mylibft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
