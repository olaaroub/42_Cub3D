# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/01 02:28:03 by olaaroub          #+#    #+#              #
#    Updated: 2025/01/21 16:54:41 by olaaroub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -fsanitize=address -g3
MAKEFLAGS := --no-print-directory

# ITALICBOLD
GREEN = \033[0;32m
RESET = \033[0m
BOLD = \033[1m
LARGE = \033[2m
SRC = $(wildcard src_parsing/*.c)
SRC += $(wildcard src_execution/*.c)
SRC += $(wildcard tools/*.c)

OBJ = $(SRC:.c=.o)

NAME = Cub3D
LIB = libft/libft.a
MINILIBX = minilibx-linux/libmlx_Linux.a
HEADER = inc/cub3d.h

all: $(NAME)

$(NAME): $(OBJ) $(LIB) $(MINILIBX) $(HEADER)
	@stty -echoctl
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm -o $(NAME)
	make clean
	@echo "✅ $(LARGE)$(BOLD)$(GREEN)$(NAME)$(RESET)"


$(MINILIBX):
	@make -C minilibx-linux
	@echo "✅ $(LARGE)$(BOLD)$(GREEN)minilibx$(RESET)"

$(LIB):
	@make -j -C libft
	@echo "✅ $(LARGE)$(BOLD)$(GREEN)libft$(RESET)"

clean:
	@rm -rf $(OBJ)
	@make clean -C libft

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIB)
	@make clean -C minilibx-linux

re:
	@make fclean
	@make all

.PHONY: all fclean clean re bonus
.SECONDARY: $(OBJ)
.SILENT: $(OBJ) $(NAME) $(MINILIBX) $(LIB)