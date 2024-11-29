# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/29 18:33:25 by olaaroub          #+#    #+#              #
#    Updated: 2024/11/29 18:48:05 by olaaroub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -fsanitize=address -g3
MAKEFLAGS := -j --no-print-directory

# ITALICBOLD
GREEN = \033[0;32m
RESET = \033[0m
SRC += $(wildcard ./*.c)
# SRC += $(wildcard src_parsing/*.c)

OBJ = $(SRC:.c=.o)

NAME = cub3D
LIB = libft/libft.a
MINILIBX = minilibx-linux/libmlx_Linux.a

all: $(NAME)

$(NAME): $(OBJ) $(LIB) $(MINILIBX)
	@stty -echoctl
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -Lminilibx-linux -lmlx_Linux -lX11 -lXext -o $(NAME)
	make clean
	@echo "✅ $(GREEN)$(NAME)$(RESET)"


$(MINILIBX):
	@$(MAKE) -C minilibx-linux
	@echo "✅ $(GREEN)minilibx$(RESET)"

$(LIB):
	@$(MAKE) -C libft
	@echo "✅ $(GREEN)libft$(RESET)"

clean:
	@rm -rf $(OBJ)
	@make clean -C minilibx-linux
	@make clean -C libft

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIB)
	@rm -rf $(MINILIBX)

re:
	@make fclean
	@make all

.PHONY: all fclean clean re bonus
.SECONDARY: $(OBJ)
.SILENT: $(OBJ) $(NAME)
