# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 17:20:01 by olaaroub          #+#    #+#              #
#    Updated: 2025/02/04 17:40:45 by olaaroub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC			= cc
CFLAGS		= -Wall -Wextra -Werror
CFLAGS		+=  -fsanitize=address  -g3
MAKEFLAGS	:= --no-print-directory

GREEN		= \033[0;32m
RESET		= \033[0m
BOLD		= \033[1m
LARGE		= \033[2m

BONUS		= 0
MLX			= minilibx-linux/libmlx.a
LIBFT		= libft/libft.a

SRC_PATH 	= ./sources/
SRC			= 	main.c \
			init/init.c \
			init/init_utils.c \
			parsing/check_map.c \
			parsing/parse_textures.c \
			parsing/parse_colors.c \
			parsing/parse_map.c \
			utils/trash.c \
			utils/utils-v1.c \
			utils/utils-v2.c \
			utils/utils-v3.c \
			utils/parsing_utils.c \
			render/render.c \
			render/get_texture_pixels.c\
			render/raycast.c \
			render/minimap.c \
			mouvements/keys.c \
			mouvements/moves.c \

SRCS		= $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH	= ./objects/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

INC			=	-I ./includes/\
				-I ./libft/\
				-I ./minilibx-linux/
HEADER		= ./includes/cub3d.h
VARIABLES	= ./includes/variables.h

NAME		= cub3D

all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/init
	mkdir -p $(OBJ_PATH)/parsing
	mkdir -p $(OBJ_PATH)/render
	mkdir -p $(OBJ_PATH)/utils
	mkdir -p $(OBJ_PATH)/mouvements

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) -c $< -o $@ $(INC)

$(NAME): $(OBJS) $(HEADER) $(VARIABLES)
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm
	@echo "✅ $(LARGE)$(BOLD)$(GREEN)minilibx$(RESET)"
	@echo "✅ $(LARGE)$(BOLD)$(GREEN)$(NAME)$(RESET)"

$(LIBFT):
	make -j -sC libft/
	make clean -sC libft/
	@echo "✅ $(LARGE)$(BOLD)$(GREEN)libft$(RESET)"

$(MLX):
	@make -sC minilibx-linux/

bonus:
	@make re  BONUS=1

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all
.PHONY: all clean fclean re bonus
.SILENT:$(OBJ_PATH) $(OBJS) $(LIBFT) $(MLX) $(NAME)
.SECONDARY: $(OBJS) $(NAME) $(OBJ_PATH) $(LIBFT) $(MLX)