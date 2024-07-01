# Compiler and flags
CC := clang
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address

# Project name and directories
NAME := so_long
SRC_DIR := .
OBJ_DIR := obj

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries
MLX_DIR := .
MLX_LIB := $(MLX_DIR)/libmlx.a
FRAMEWORKS := -framework OpenGL -framework AppKit

# Targets and rules
all: $(NAME)

$(NAME): $(OBJS) | $(MLX_LIB)
	@echo "Linking $@"
	@$(CC) $(CFLAGS) -o $@ $^ $(MLX_LIB) $(FRAMEWORKS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(MLX_LIB):
	@echo "MLX library not found. Please make sure libmlx.a is in the current directory."
	@exit 1

clean:
	@echo "Cleaning object files"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Cleaning executable"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re