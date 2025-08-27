# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 08:44:04 by juwang            #+#    #+#              #
#    Updated: 2025/05/07 10:06:01 by juwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
HDRS = libft.h

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	  ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	  ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	  ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strchr.c ft_strdup.c \
	  ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
	  ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_split.c \
	  ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

SRC_BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
			ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

BONUS_FLAG=	.bonus_flag

# 2. 目標規則 - 通用 .c 轉 .o 的規則
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 3. 主目標：編譯 libft.a（包含 bonus）
$(NAME): $(OBJ) $(OBJ_BONUS)
	@ar rcs $(NAME) $(OBJ) $(OBJ_BONUS)

# 4. bonus 目標：編譯 bonus 函數並加入靜態庫
bonus: $(BONUS_FLAG)

$(BONUS_FLAG): $(OBJ) $(OBJ_BONUS)
	ar rcs $(NAME) $(OBJ) $(OBJ_BONUS)
	@touch $(BONUS_FLAG)


# 5. all 目標：預設執行 bonus（因為評分用 bonus）
all: bonus

# 6. 清除 .o 檔
clean:
	rm -f $(OBJ) $(OBJ_BONUS)

# 7. 清除 .a 檔與 .o 檔
fclean: clean
	rm -f $(NAME)

# 8. 重新編譯
re: fclean all

# 9. 聲明不是真實檔案
.PHONY: all clean fclean re bonus
