/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:51:20 by ohammou-          #+#    #+#             */
/*   Updated: 2024/10/10 20:20:00 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include "minilibx-linux/mlx.h"
#include "tools/libft/libft.h"
#include "tools/get_next_line/get_next_line.h"

typedef struct s_map
{
	char **map;
	char **texture;
	char **floor_color;
	char *color;
	char *textur_as_lien;
	char *map_as_lien;
	int  flag;
}	t_map;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_data
{
	void			*mlx;
	void			*mlx_win;
	int				x;
	int				y;
	int				len_x;
	int				len_y;
	int				x_max;
	int				y_max;
	int				i;
	int				j;
	int				fd;
	int				is_drawing;
	unsigned int	color_wall;
	unsigned int	color;
	unsigned int	color_player;
	t_map			map;
	int				offset;
}	t_data;


void	check_option(char *str);
int		is_texture(char *line);
int		is_color(char *line);
int		is_white_space(char c);
int 	is_emty(char *line);
t_map   read_map(char *file);
void    free_trash(t_list **trash);
void    add_to_trash(void *add, t_list **trash);
void	ft_error(char *str);
void 	check_wall(t_map *map);
void 	check_wall2(t_map *map);
char	**duplicate_map(char **map);
int		ft_strlen_blm9lob(char **map);
void    free_map(char **map);
void	check_player(char **map);
t_data	*data_global();
void	get_postion(t_data *data, char **map);
void	flodfile(char **map, int i, int j);
void	check_floodfile(char **map);

// -----------------------------------

void	main_of_drawing();
int 	mouse(int botton,int key, int y, void *par);
int		esc(int key, void *param);
int		krwa();
void	open_the_window();
int 	drawing();
int		move(int key, void *parm);
void	get_data_addr(t_img *img);
void 	put_and_destroy_img(t_img *img);

#endif
