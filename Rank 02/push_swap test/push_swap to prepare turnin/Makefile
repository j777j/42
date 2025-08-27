# --- Compiler and Flags ---
CC = clang
CFLAGS = -Wall -Wextra -Werror -I includes -I mylibft

# --- Executable Name ---
NAME = push_swap

# --- Library ---
LIB_DIR = mylibft
LIB = $(LIB_DIR)/mylibft.a
LDFLAGS = -L$(LIB_DIR) -l:mylibft.a

# --- Source Files ---
VPATH = src:src/operations

SRCS = main.c \
       init.c \
       parse.c \
       parse2.c \
       simplify.c \
       greedy.c \
       greedy2.c \
       execute_move.c \
       execute_move2.c \
       sort_small.c \
       utils.c \
       utils2.c \
       swap.c \
       push.c \
       rotate.c \
       reverse_rotate.c

# --- Object Files ---
OBJS = $(SRCS:.c=.o)

# --- Rules ---
all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(LIB):
	@$(MAKE) -C $(LIB_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
