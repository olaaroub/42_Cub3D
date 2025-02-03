/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:51:20 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/03 01:04:34 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "variables.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef BONUS
#  define BONUS 1
# endif

typedef struct s_map
{
	char			**map;
	char			**texture;
	char			**floor_color;
	char			*color;
	char			*texture_line;
	char			*map_line;
	int				ceiling_hex;
	int				floor_hex;
	int				flag;
}					t_map;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_texture
{
	void			*texture;
	char			*addr;
	char			*path;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;

}					t_texture;

typedef struct s_vect
{
	double			x;
	double			y;

}					t_vect;

typedef struct s_minimap
{
	int				len;
	int				flag;
	t_vect			circle_center;
	int				offset;
}					t_minimap;

typedef struct s_animations
{
	t_texture		**door_tex;
	t_texture		**fire_tex;
	t_texture		**hand_tex;
	int				hand_curr_frame;
	int				fire_curr_frame;
	int				door_curr_frame;
	bool			fire_switch;
	double			anim_time;
	int				hand_y_offset;

}					t_animations;

typedef struct s_moves
{
	int				turn_right;
	int				turn_left;
	int				a_pressed;
	int				d_pressed;
	int				w_pressed;
	int				s_pressed;
	bool			opened;

}					t_moves;

typedef struct s_data
{
	t_texture		*north_tex;
	t_texture		*south_tex;
	t_texture		*west_tex;
	t_texture		*east_tex;
	t_animations	*animations;
	t_map			*map;
	t_img			*img;
	t_minimap		*minimap;
	t_list			**trash;
	t_moves			moves;
	t_vect			player;
	t_vect			hit;
	void			*mlx;
	void			*mlx_win;
	double			angle;
	double			start_angle;
	double			ray_dist;
	double			projection_dist;
	double			wallhight;
	double			start_draw;
	double			end_draw;
	int				x_max;
	int				y_max;
	bool			is_vertical;
	bool			hit_door;
	bool			hit_fire;
	bool			hit_open_door;
}					t_data;

void				free_trash(t_list **trash);
void				check_argument(char **av, int ac, t_data *data);
int					is_texture(char *line);
int					is_color(char *line);
int					is_empty(char *line);
t_map				*read_map(char *file);
void				add_to_trash(void *add, t_list **trash);
void				ft_error(char *str);
char				**duplicate_map(char **map);
int					count_coloumns(char **map);
void				free_map(char **map);
void				check_player(char **map);
t_data				*data_global(void);
void				get_postion(t_data *data, char **map);
bool				is_valid_number(char *str);
void				pars_the_color(t_data *data);
int					cont_character(char *str, int c);
void				main_of_drawing(t_data *data);
int					rgb_to_hex(int r, int g, int b);
int					exit_key(void *data);
int					move(void *parm);
void				ft_pixelput(t_img *img, int x, int y, int color);
int					key_release(int key, void *parm);
int					key_press(int key, void *parm);
void				render_3d(t_data *data);
void				initialize_variables(t_data *data);
bool				check_if_surrounded(char **map);
void				pars_texture(t_data *data);
int					get_x_max(char **map);
void				minimap(t_data *data);
#endif
