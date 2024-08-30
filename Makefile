# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 15:55:27 by lmeubrin          #+#    #+#              #
#    Updated: 2024/08/27 18:43:36 by lmeubrin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash
MAKEFLAGS += --warn-undefined-variables
.ONESHELL:

CC := cc
CFLAGS := -Werror -Wall -Wextra -g -I$(HDRS_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
NAME := fractol

# fsanitize
SANITIZE_NAME := $(NAME)_sanitize
SANITIZE_FLAGS := -fsanitize=address,undefined

#Libft
LIBFT_DIR := lib/libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_FLAGS := -L$(LIBFT_DIR) -lft

#MiniLibX
MLX_DIR := lib/mlx
MLX_FLAGS := -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm
LIBMLX := $(MLX_DIR)/libmlx.a

OBJ_DIR := obj

SRCS := main.c

OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

HDRS_DIR := include
HDRS := $(HDRS_DIR)/fractol.h

#PRETTY
$BOLD := \033[1m
$RESET := \033[0m

.PHONY: all, clean, fclean, re, submodules

all: $(LIBFT) $(LIBMLX) $(NAME)

run: all
	./$(NAME)

# Compiling MiniLibX. Clones from official repo if not present.
# Output of cloning / compiliation supressed via redirecting '>/dev/null 2>&1'.
$(LIBMLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MiniLibX repository..."; \
		git submodule add https://github.com/42Paris/minilibx-linux.git $(MLX_DIR) >/dev/null 2>&1; \
	fi
	@echo "Compiling MiniLibX..."
	@make -s -C $(MLX_DIR) >/dev/null 2>&1;
	@echo "$(BOLD)MiniLibX compiled.$(RESET)"

# Submodules in my own Libft from own repo if not present and compiles
$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Cloning own Libft repository"; \
		git submodule add git@github.com:Moat423/Libft_full.git $(LIBFT_DIR); \
	fi
	@git submodule status libft | grep -q '^-' && \
		echo "Initializing libft and its submodules..." && \
		git submodule update --init --recursive || true;
		$(MAKE) -C $(LIBFT_DIR) >dev/null 2>&1;

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(MLX_FLAGS) $(OBJS) $(LIBFT) -o $@

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

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
