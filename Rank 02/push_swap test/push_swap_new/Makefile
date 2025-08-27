# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/13 00:00:00 by juwang            #+#    #+#              #
#    Updated: 2025/07/13 00:00:00 by juwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror -I includes

NAME = push_swap_new

VPATH = src:src/operations

SRCS = main.c \
       init.c \
       parse.c \
       ranking.c \
       algorithm.c \
       partition.c \
       greedy.c \
       final_alignment.c \
       sort_small.c \
       utils.c \
       swap.c \
       push.c \
       rotate.c \
       reverse_rotate.c

OBJS = $(SRCS:.c=.o)

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
