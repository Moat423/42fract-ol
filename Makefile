# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 15:55:27 by lmeubrin          #+#    #+#              #
#    Updated: 2024/09/02 17:04:23 by lmeubrin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash
MAKEFLAGS += --warn-undefined-variables
.ONESHELL:

CC := cc
CFLAGS := -Werror -Wall -Wextra
INCLUDES := -I$(HDRS_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(MLX_DIR)
NAME := fractol

# fsanitize
SANITIZE_NAME := $(NAME)_sanitize
SANITIZE_FLAGS := -fsanitize=address,undefined

#Libft
LIBFT_DIR := ./lib/libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_FLAGS := -L$(LIBFT_DIR) -lft

#MiniLibX
MLX_DIR := ./lib/mlx
MLX_FLAGS := -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
MLX_INLC := -I$(MLX_DIR)
LIBMLX := $(MLX_DIR)/libmlx.a

OBJ_DIR := obj

SRCS := main.c image.c clean_n_close.c hooks.c

OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

HDRS_DIR := include
HDRS := $(HDRS_DIR)/fractol.h

#PRETTY
BOLD := \033[1m
RESET := \033[0m
RED := \033[31;2m
GREEN := \033[32m
YELLOW := \033[33m

.PHONY: all, clean, fclean, re

all: $(LIBFT) $(LIBMLX) $(NAME)

run: all
	./$(NAME)

# Compiling MiniLibX. Clones from official repo if not present.
# Output of cloning / compiliation supressed via redirecting '>/dev/null 2>&1'.
$(LIBMLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MiniLibX repository..."; \
		git submodule add https://github.com/42Paris/minilibx-linux.git $(MLX_DIR) >/dev/null 2>&1; \
		git submodule init && git submodule update
	fi
	@echo "Compiling MiniLibX..."
	@make -s -C $(MLX_DIR) >/dev/null 2>&1;
	@echo "$(BOLD)MiniLibX compiled.$(RESET)"

# Submodules in my own Libft from own repo if not present and compiles
$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ] || [ -z "$$(ls -A $(LIBFT_DIR))" ]; then \
		echo "Initializing libft and its submodules..."; \
		git submodule add -f git@github.com:Moat423/Libft_full.git $(LIBFT_DIR); \
		git submodule update --init --recursive -- $(LIBFT_DIR); \
	else \
		echo "Updating libft and its submodules..."; \
		git submodule update --init --recursive -- $(LIBFT_DIR); \
	fi
	@make -s -C $(LIBFT_DIR) > /dev/null 2>&1

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	@printf "%b\rLinking %s %b\n" "$(BOLD)" "$(NAME)" "$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $@
	@printf "%b\r%b%s%b successfully compiled.\n" "$(BOLD)" "$(YELLOW)" "$(NAME)" "$(RESET)"

$(OBJ_DIR)/%.o: %.c $(HDRS)
	mkdir -p $(OBJ_DIR)
	@printf "%b\rCompiling %s %b\n" "$(BOLD)" "$(NAME)" "$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	@rm -rf $(MLX_DIR)
	@rm -dRf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean 2>&1
	@echo "Objects and libraries (except libft) removed"

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

sanitize: CFLAGS += $(SANITIZE_FLAGS)
sanitize: LDFLAGS += $(SANITIZE_FLAGS)

sanitize: CFLAGS += $(SANITIZE_FLAGS)
sanitize: re
