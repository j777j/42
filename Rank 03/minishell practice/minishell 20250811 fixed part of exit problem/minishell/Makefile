# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 12:00:00 by juwang            #+#    #+#              #
#    Updated: 2025/07/24 14:30:14 by juwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# --- Compiler and Flags ---
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# For readline library
# On MacOS, readline might be in a different path.
# You might need: -I/goinfre/homebrew/opt/readline/include
# And LDFLAGS: -L/goinfre/homebrew/opt/readline/lib
READLINE_INC = -I/usr/include/readline
READLINE_LIB = -L/usr/lib -lreadline

# --- Directories ---
SRC_DIR = src
BUILTIN_DIR = src/builtins
INC_DIR = includes
LIBFT_DIR = libft

# --- Source Files ---
SRCS =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/signals.c \
		$(SRC_DIR)/lexer.c \
		$(SRC_DIR)/lexer_utils.c \
		$(SRC_DIR)/parser.c \
		$(SRC_DIR)/parser_utils.c \
		$(SRC_DIR)/executor.c \
		$(SRC_DIR)/executor_utils.c \
		$(SRC_DIR)/expander.c \
		$(SRC_DIR)/expander_utils.c \
		$(SRC_DIR)/expander_split.c \

BUILTIN_SRCS = $(wildcard $(BUILTIN_DIR)/*.c)

OBJS = $(SRCS:.c=.o)
BUILTIN_OBJS = $(BUILTIN_SRCS:.c=.o)

# --- Libft ---
LIBFT = $(LIBFT_DIR)/libft.a

# --- Rules ---
all: $(NAME)

$(NAME): $(OBJS) $(BUILTIN_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(BUILTIN_OBJS) -I$(INC_DIR) $(LIBFT) $(READLINE_LIB)

$(LIBFT):
	@make -C $(LIBFT_DIR) re

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR) -I$(LIBFT_DIR) $(READLINE_INC)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJS) $(BUILTIN_OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re