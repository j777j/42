CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

NAME = philo

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/philosopher.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/philo_actions.c \
	$(SRC_DIR)/monitor_checks.c \
	$(SRC_DIR)/initialization.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
