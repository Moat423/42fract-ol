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
MAKEFLAGS += --no-print-directory --warn-undefined-variables

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
# BOLD := \033[1m
# RESET := \033[0m
# RED := \033[31;2m
# GREEN := \033[32m
# YELLOW := \033[33m
# CLEAR_LINE := \033[2K
# CURSOR_UP := \033[A
BOLD := $(shell printf '\033[1m')
RESET := $(shell printf '\033[0m')
RED := $(shell printf '\033[31;2m')
GREEN := $(shell printf '\033[32m')
YELLOW := $(shell printf '\033[33m')
CLEAR_LINE := $(shell printf '\033[2K')
CURSOR_UP := $(shell printf '\033[1A')

# Additional pretty printing variables
TOTAL_FILES := $(words $(SRCS))
CURRENT_FILE := 0
PROGRESS_BAR_WIDTH := 40

define update_progress
    @printf "$(CLEAR_LINE)"
    @printf "\r$(YELLOW)Compiling: $(RESET)["
    @$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
    @$(eval PERCENTAGE=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
    @$(eval FILLED=$(shell echo $$(($(PERCENTAGE) * $(PROGRESS_BAR_WIDTH) / 100))))
    @$(eval EMPTY=$(shell echo $$(($(PROGRESS_BAR_WIDTH) - $(FILLED)))))
    @printf "%*s" ${FILLED} "" | tr ' ' '='
    @printf "%*s" ${EMPTY} "" | tr ' ' ' '
    @printf "] %3d%% %s" $(PERCENTAGE) "$<"
endef

.PHONY: all clean fclean re sanitize asan ubsan leak

all: $(LIBFT) $(LIBMLX) $(NAME)

run: all
	./$(NAME)

# Main program
$(NAME): $(LIBFT) $(LIBMLX) $(OBJS)
	@printf "\n$(BOLD)Linking $(NAME)$(RESET)\n"
	$(CC) $(FINAL_CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) $(FINAL_LDFLAGS) -o $@
	printf "\n$(GREEN)$(BOLD)Build successful!$(RESET)\n" || \
	printf "$(RED)$(BOLD)Build failed!$(RESET)\n"

# Compile object files
$(OBJ_DIR)/%.o: %.c $(LIBMLX) | $(OBJ_DIR)
	$(call update_progress)
	@$(CC) $(FINAL_CFLAGS) $(INCLUDES) -c $< -o $@

# # Create/update flags file
# .PRECIOUS: $(OBJ_DIR)/.flags
# $(OBJ_DIR)/.flags: | $(OBJ_DIR)
# 	@printf "$(FINAL_CFLAGS) $(INCLUDES)" > $@

# Create obj directory
$(OBJ_DIR):
	@mkdir -p $@

#LIBRARIES
# Compiling MiniLibX. Clones from official repo if not present.
# Output of cloning / compiliation supressed via redirecting '>/dev/null 2>&1'.
$(LIBMLX):
	@mkdir -p lib
	@if [ ! -d "$(MLX_DIR)" ] || [ -z "$$(ls -A $(MLX_DIR))" ]; then \
		printf "$(BOLD)Initializing MinilibX...$(RESET)\n"; \
		git submodule add https://github.com/42Paris/minilibx-linux.git $(MLX_DIR) >/dev/null 2>&1; \
		git submodule init >/dev/null 2>&1 && git submodule update >/dev/null 2>&1
	fi
	@printf "$(BOLD)Building MinilibX...$(RESET)\n"
	@make -s -C $(MLX_DIR) >/dev/null 2>&1;

# Submodules in my own Libft from own repo if not present and compiles
$(LIBFT):
	@mkdir -p lib
	@if [ ! -d "$(LIBFT_DIR)" ] || [ -z "$$(ls -A $(LIBFT_DIR))" ]; then \
		printf "$(BOLD)Initializing libft...$(RESET)\n"; \
		git submodule add https://github.com/Moat423/Libft_full.git $(LIBFT_DIR); \
		git submodule update --init --recursive -- $(LIBFT_DIR); \
	else \
		printf "$(BOLD)Updating libft...$(RESET)\n"; \
		git submodule update --init --recursive -- $(LIBFT_DIR); \
	fi
	@make -s -C $(LIBFT_DIR) > /dev/null 2>&1

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
sanitize: fclean $(NAME)

clean:
	@printf "$(BOLD)Cleaning object files...$(RESET)\n"
	@rm -rf $(MLX_DIR)
	@rm -dRf $(OBJ_DIR)
	@rm -f $(OBJ_DIR)/.flags
	@make -s -C $(LIBFT_DIR) clean 2>&1

fclean: clean
	@printf "$(BOLD)Cleaning executables...$(RESET)\n"
	@rm -f $(NAME)
	@make -s -C $(LIBFT_DIR) fclean >/dev/null 2>&1

re: fclean all
