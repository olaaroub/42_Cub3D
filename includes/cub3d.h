/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:51:20 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/06 03:28:42 by olaaroub         ###   ########.fr       */
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
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_texture
{
	void			*texture;
	char			*addr;
	char			*path;
	int				bpp;
	int				line_len;
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
	t_vect			player;
	int				map_x;
	int				map_y;
	double			rot_angle;
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

typedef struct s_raycast_vars
{
	bool			hit_door_h;
	bool			hit_door_v;
	bool			hit_door_oh;
	bool			hit_door_ov;
	bool			hit_fire_h;
	bool			hit_fire_v;
	t_vect			h_hit;
	t_vect			v_hit;
	t_vect			hit;
	t_vect			step;
	t_vect			map;
}					t_raycast_vars;

typedef struct s_data
{
	t_texture		*north_tex;
	t_texture		*south_tex;
	t_texture		*west_tex;
	t_texture		*east_tex;
	t_animations	*anim;
	t_map			*map;
	t_img			*img;
	t_minimap		*minimap;
	t_list			*trash;
	t_moves			moves;
	t_vect			player;
	t_vect			hit;
	t_raycast_vars	*vars_h;
	t_raycast_vars	*vars_v;
	void			*mlx;
	void			*mlx_win;
	double			two_pi;
	double			field_of_view;
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
	int				old_x;
}					t_data;
//					** Initialization **
void				init_game(t_data *data);
void				initialize_variables(t_data *data);
void				get_postion(t_data *data, char **map);

// 					** Parsing **

void				check_element(t_data *data, t_map *map, char *line);
int					is_texture(char *line);
int					is_color(char *line);
int					is_empty(char *line);
void				resize_map(t_data *data, t_map *map);
int					get_x_max(char **map);
void				skip_trailing_nl(t_data *data, t_map *map);
void				add_double_ptr_to_trash(t_data *data, void **add);
bool				is_valid_number(char *str);
t_map				*read_map(t_data *data, char *file);
bool				check_if_surrounded(t_data *data, char **map);

// 					** Rendering **
void				get_position_of_player_in_minimap(t_data *data, int x_draw,
						int y_draw);
void				render(t_data *data);
double				raycast(t_data *data);
int					get_vertical_color(t_data *data, double y);
int					get_horizontal_color(t_data *data, double y);
void				game_loop(t_data *data);
void				horizontal_intersection(t_data *data, t_vect *hit);
void				vertical_intersection(t_data *data, t_vect *hit);
int					hit_tile_v(t_data *data, t_raycast_vars *vars);
int					hit_tile_h(t_data *data, t_raycast_vars *vars);

// 					** keys moves**
int					exit_key(void *data);
void				ft_error(t_data *data, char *str, int exit_code);
int					mouse_input(int x, int y, void *param);
void				add_to_trash(t_list **trash, void *add);
int					apply_moves(void *parm);
void				free_trash(t_list **trash);
void				open_door(t_data *data);
void				close_door(t_data *data);
void				move_up(t_data *data);
void				move_down(t_data *data);
void				move_left(t_data *data);
void				move_right(t_data *data);

int					count_chars(char *str, int c);

int					count_coloumns(char **map);
void				pars_the_color(t_data *data);
int					count_chars(char *str, int c);
void				game_loop(t_data *data);
int					rgb_to_hex(t_data *data, int r, int g, int b);
void				ft_pixelput(t_img *img, int x, int y, int color);
int					key_release(int key, void *parm);
int					key_press(int key, void *parm);
void				pars_texture(t_data *data);
void				minimap(t_data *data);
#endif
