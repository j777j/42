# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 09:35:07 by juwang            #+#    #+#              #
#    Updated: 2025/07/04 09:35:16 by juwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Compiler and Flags ---
CC = clang
CFLAGS = -Wall -Wextra -Werror -I includes

# --- Executable Name ---
NAME = push_swap

# --- Source Files ---
VPATH = src:src/operations

SRCS = main.c \
       init.c \
       parse.c \
       setup.c \
       simplify.c \
       algorithm.c \
       general_sort.c \
       chunking.c \
       greedy.c \
       execute_move.c \
       final_alignment.c \
       sort_small.c \
       utils.c \
       swap.c \
       push.c \
       rotate.c \
       reverse_rotate.c

# --- Object Files ---
OBJS = $(SRCS:.c=.o)

# --- Rules ---
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
