NAME = cub3D
CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft -Ilib/minilibx-linux
MLXFLAGS = -Llib/minilibx-linux -lmlx -lXext -lX11 -lm -lbsd
LIBFT = libft/libft.a
SRCS = src/main.c src/parser.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re