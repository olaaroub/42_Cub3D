# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 17:20:01 by olaaroub          #+#    #+#              #
#    Updated: 2025/01/28 19:02:20 by olaaroub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


MAKEFLAGS := --no-print-directory

NAME	= cub3D

BONUS = 0

CC		= cc
CFLAGS	= -Werror -Wextra -Wall
CFLAGS +=  -fsanitize=address -O3 -g3

MLX			= minilibx-linux/libmlx.a

LIBFT		= libft/libft.a

SRC_PATH = ./src/
SRC		= 	main.c \
			src_parsing/is_surrounded.c \
			src_parsing/pars_texture.c \
			src_parsing/read_colors.c \
			src_parsing/read_map.c \
			tools/trash.c \
			tools/utils-v1.c \
			tools/utils-v2.c \
			tools/utils-v3.c \
			src_execution/draw.c \
			src_execution/drawing_rays.c \
			src_execution/drawing.c \
			src_execution/keys.c \
			src_execution/keys2.c \
			
SRCS	= $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH	= ./objects/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

INC			=	-I ./inc/\
				-I ./libft/\
				-I ./minilibx-linux/

all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/src_execution
	mkdir -p $(OBJ_PATH)/src_parsing
	mkdir -p $(OBJ_PATH)/tools

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm

$(LIBFT):
	make -sC libft/

# MLX rule
$(MLX):
	make -sC minilibx-linux/

bonus:
	make all  BONUS=1

clean:
	rm -rf $(OBJ_PATH)
	make clean -C libft
	make clean -C minilibx-linux

# Remove program executable
fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all