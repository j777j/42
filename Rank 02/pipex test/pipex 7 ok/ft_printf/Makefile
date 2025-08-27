# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/18 10:43:23 by juwang            #+#    #+#              #
#    Updated: 2025/07/13 06:55:56 by juwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c \
      ft_printf_utils1.c \
	  ft_printf_utils2.c \

OBJ = $(SRC:.c=.o)

LIBFT_DIR = ../libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

HEADERS = -I. -I$(LIBFT_DIR)

all: $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT_LIB)
	ar rcs $(NAME) $(OBJ) $(LIBFT_LIB)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

test: all
	cc main.c $(NAME) $(LIBFT_LIB) -o test
