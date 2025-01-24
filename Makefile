# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 15:55:27 by lmeubrin          #+#    #+#              #
#    Updated: 2024/09/14 11:07:31 by lmeubrin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash
.ONESHELL:
MAKEFILES := lib/libft/Makefile lib/mlx/Makefile
MAKEFLAGS += --warn-undefined-variables

#headers directories
HDRS_DIR := include
LIBFT_DIR := lib/libft
MLX_DIR := lib/mlx
OBJ_DIR := obj

CC := cc
NAME := fractol
INCLUDES := -I$(HDRS_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

#flags
CFLAGS := -Werror -Wall -Wextra -g
LDFLAGS :=
SANITIZE_FLAGS := -fsanitize=address,undefined

FINAL_CFLAGS = $(CFLAGS)
FINAL_LDFLAGS = $(LDFLAGS)

# Different sanitizer configurations
ASAN_FLAGS := -fsanitize=address
UBSAN_FLAGS := -fsanitize=undefined
LEAK_FLAGS := -fsanitize=leak

# Targets for different sanitizer builds
asan: FINAL_CFLAGS = $(CFLAGS) $(ASAN_FLAGS)
asan: FINAL_LDFLAGS = $(LDFLAGS) $(ASAN_FLAGS)
asan: fclean $(NAME)

ubsan: FINAL_CFLAGS = $(CFLAGS) $(UBSAN_FLAGS)
ubsan: FINAL_LDFLAGS = $(LDFLAGS) $(UBSAN_FLAGS)
ubsan: fclean $(NAME)

leak: FINAL_CFLAGS = $(CFLAGS) $(LEAK_FLAGS)
leak: FINAL_LDFLAGS = $(LDFLAGS) $(LEAK_FLAGS)
leak: fclean $(NAME)

# Combined sanitizer (your original sanitize target)
sanitize: FINAL_CFLAGS = $(CFLAGS) $(SANITIZE_FLAGS)
sanitize: FINAL_LDFLAGS = $(LDFLAGS) $(SANITIZE_FLAGS)
sanitize: $(NAME)

# fsanitize
# SANITIZE_NAME := $(NAME)_sanitize

#Libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_FLAGS := -L$(LIBFT_DIR) -lft

#MiniLibX
MLX_FLAGS := -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
LIBMLX := $(MLX_DIR)/libmlx.a

SRCS := main.c image.c clean_n_close.c hooks.c julia.c colour.c \
		mandelbrot.c keys.c tricorn.c inits.c

OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)
HDRS := $(HDRS_DIR)/fractol.h

#PRETTY
BOLD := \033[1m
RESET := \033[0m
RED := \033[31;2m
GREEN := \033[32m
YELLOW := \033[33m

.PHONY: all clean fclean re sanitize asan ubsan leak

all: $(LIBFT) $(LIBMLX) $(NAME)

run: all
	./$(NAME)

# Compiling MiniLibX. Clones from official repo if not present.
# Output of cloning / compiliation supressed via redirecting '>/dev/null 2>&1'.
$(LIBMLX):
	@mkdir -p lib
	@if [ ! -d "$(MLX_DIR)" ] || [ -z "$$(ls -A $(MLX_DIR))" ]; then \
		echo "Cloning MiniLibX repository..."; \
		git submodule add https://github.com/42Paris/minilibx-linux.git $(MLX_DIR) >/dev/null 2>&1; \
		git submodule init && git submodule update
	fi
	@echo "Compiling MiniLibX..."
	@make -s -C $(MLX_DIR) >/dev/null 2>&1;
	@echo "$(BOLD)MiniLibX compiled.$(RESET)"

# Submodules in my own Libft from own repo if not present and compiles
$(LIBFT):
	@mkdir -p lib
	@if [ ! -d "$(LIBFT_DIR)" ] || [ -z "$$(ls -A $(LIBFT_DIR))" ]; then \
		echo "Initializing libft and its submodules..."; \
		git submodule add https://github.com/Moat423/Libft_full.git $(LIBFT_DIR); \
		git submodule update --init --recursive -- $(LIBFT_DIR); \
	else \
		echo "Updating libft and its submodules..."; \
		git submodule update --init --recursive -- $(LIBFT_DIR); \
	fi
	@make -s -C $(LIBFT_DIR) > /dev/null 2>&1
# Create obj directory
$(OBJ_DIR):
	@mkdir -p $@

# Create/update flags file
.PRECIOUS: $(OBJ_DIR)/.flags
$(OBJ_DIR)/.flags: | $(OBJ_DIR)
	@echo '$(FINAL_CFLAGS) $(INCLUDES)' > $@

# Compile object files - adding $(OBJ_DIR) as prerequisite
$(OBJ_DIR)/%.o: %.c $(HDRS) $(LIBMLX) | $(OBJ_DIR)
	@echo -e "$(BOLD)Compiling $<$(RESET)"
	@$(CC) $(FINAL_CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(LIBMLX) $(OBJS)
	@echo -e "$(BOLD)Linking $(NAME)$(RESET)"
	$(CC) $(FINAL_CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) $(FINAL_LDFLAGS) -o $@
	@echo -e "$(BOLD)$(YELLOW)$(NAME)$(RESET) successfully compiled."

# $(NAME): $(LIBFT) $(LIBMLX) $(OBJS)
# 	@echo -e "$(BOLD)Linking $(NAME)$(RESET)"
# 	$(CC) $(FINAL_CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) $(FINAL_LDFLAGS) -o $@
# 	@echo -e "$(BOLD)$(YELLOW)$(NAME)$(RESET) successfully compiled."
#
# # Create obj directory
# $(OBJ_DIR):
# 	@mkdir -p $@
#
# # Create/update flags file
# .PRECIOUS: $(OBJ_DIR)/.flags
# $(OBJ_DIR)/.flags: | $(OBJ_DIR)
# 	@echo '$(FINAL_CFLAGS) $(INCLUDES)' > $@
#
# # Update object compilation to depend on the flags file
# $(OBJ_DIR)/%.o: $(OBJ_DIR)/.flags %.c $(HDRS)
# 	@mkdir -p $(OBJ_DIR)
# 	@echo -e "$(BOLD)Compiling $<$(RESET)"
# 	@$(CC) $(FINAL_CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(MLX_DIR)
	@rm -dRf $(OBJ_DIR)
	@rm -f $(OBJ_DIR)/.flags
	$(MAKE) -C $(LIBFT_DIR) clean 2>&1
	@echo "Objects and libraries (except libft) removed"

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
