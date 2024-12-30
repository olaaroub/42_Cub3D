# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/01 02:28:03 by olaaroub          #+#    #+#              #
#    Updated: 2024/12/25 14:36:16 by ohammou-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += #-fsanitize=address -g3
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

NAME = cub3D
LIB = libft/libft.a
MINILIBX = minilibx-linux/libmlx_Linux.a

all: $(NAME)

$(NAME): $(OBJ) $(LIB) $(MINILIBX)
	@stty -echoctl
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm -o $(NAME)
	make clean
	@echo "✅ $(LARGE)$(BOLD)$(GREEN)$(NAME)$(RESET)"


$(MINILIBX):
	@$(MAKE) -C minilibx-linux
	@echo "✅ $(LARGE)$(BOLD)$(GREEN)minilibx$(RESET)"

$(LIB):
	@$(MAKE) -C libft
	@echo "✅ $(LARGE)$(BOLD)$(GREEN)libft$(RESET)"

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
.SILENT: $(OBJ) $(NAME) $(MINILIBX) $(LIB)