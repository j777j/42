# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/03 15:22:28 by juwang            #+#    #+#              #
#    Updated: 2025/07/03 17:03:41 by juwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# --- Compiler settings ---
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g # -g enables debugging info
RM = rm -f

# --- Project directories ---
SRC_DIR = src
INC_DIR = includes
OBJ_DIR = obj
BIN_DIR = bin

# --- Source files ---
# List all your .c files here
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/stack_utils.c \
       $(SRC_DIR)/stack_init_arr.c \
       $(SRC_DIR)/stack_free_arr.c \
       $(SRC_DIR)/stack_operations_helper.c \
       $(SRC_DIR)/operations_sa.c \
       $(SRC_DIR)/operations_sb.c \
       $(SRC_DIR)/operations_ss.c \
       $(SRC_DIR)/operations_pa.c \
       $(SRC_DIR)/operations_pb.c \
       $(SRC_DIR)/operations_ra.c \
       $(SRC_DIR)/operations_rb.c \
       $(SRC_DIR)/operations_rr.c \
       $(SRC_DIR)/operations_rra.c \
       $(SRC_DIR)/operations_rrb.c \
       $(SRC_DIR)/operations_rrr.c \
       $(SRC_DIR)/input_parser.c \
       $(SRC_DIR)/ranking.c \
       $(SRC_DIR)/special_cases.c \
       $(SRC_DIR)/algorithm_utils.c \
       $(SRC_DIR)/algorithm_main.c

# --- Object files ---
# .o files will be created in $(OBJ_DIR)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# --- Executable name ---
NAME = push_swap

# --- Default target ---
all: $(NAME)

# --- Create object directory if it doesn't exist ---
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

#<--- 新增：创建 bin 目录的规则
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# --- Rule to compile .c files into .o files ---
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# --- Rule to link object files into executable ---
$(NAME): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN_DIR)/$(NAME)
	@echo "Build complete! Executable: $(BIN_DIR)/$(NAME)"

# --- Clean up object files and executable ---
clean:
	$(RM) $(OBJ_DIR)/*.o

fclean: clean
	$(RM) $(BIN_DIR)/$(NAME)
	$(RM) -r $(OBJ_DIR) # Remove obj directory itself
	$(RM) -r $(BIN_DIR) # Remove bin directory itself

re: fclean all

# --- Phony targets ---
.PHONY: all clean fclean re $(OBJ_DIR) $(BIN_DIR)
