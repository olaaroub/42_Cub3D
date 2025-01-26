/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:51:20 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/26 20:37:43 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
#define CUB3D_H

#include "../minilibx-linux/mlx.h"
#include  <X11/X.h>
#include  <X11/keysym.h>
#include "../libft/libft.h"

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

// ---------define the macros for moves-----------

#define UP 119
#define DOWN 115
#define LEFT 97
#define RIGHT 100
#define ESC 65307

#define RIGHT_V 65363
#define LEFT_V 65361

#define FRM 4 // this macro to haw match  moves the player do in single clik !
#define SOP 2 // this is size of player (x and y)!
#define SOF 64 // this is square size
#define SPEED 2
#define MI_SIZE 30

#define PI 3.14159265
#define TOW_PI 6.28318530
#define ROT_SPEED 0.09
#define FOV_ANGLE PI / 3

#define EPSILON 1e-6
#define SCREEN_W 1920
#define SCREEN_H 1080

typedef struct s_map
{
	char **map;
	char **texture;
	char **floor_color;
	char *color;
	char *texture_line;
	char *map_line;
	int  ceiling_hex;
	int  floor_hex;
	int  flag;
}	t_map;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_texture
{
	void *texture;
	char *addr;
	char *path;
	int bits_per_pixel;
	int line_length;
	int endian;
	int width;
	int height;

} t_texture;

typedef struct s_vect
{
	double x;
	double y;

} t_vect;

typedef struct s_minimap
{
	int len;
	double y_start;
	double x_start;
	double x_end;
	double y_end;
	double x;
	double y;
	int i;
	int j;
	int flag;
	double tmp_x;
	double tmp_y;
} t_minimap;

typedef struct s_data
{
	t_texture		*north_tex;
	t_texture		*south_tex;
	t_texture		*west_tex;
	t_texture		*east_tex;
	t_texture		*door_tex;
	t_map			map;
	t_img			*img;
	t_minimap		minimap;
	void			*mlx;
	void			*mlx_win;
	double			player_x;
	double			player_y;
	int				x_max;
	int				y_max;
	double			angle;
	int				turn_left;
	int				turn_right;
	int				a_pressed;
	int				d_pressed;
	int				w_pressed;
	int				s_pressed;
	int				offset;
	double				px;
	double				py;
	// -------rander 3d--------
	bool			is_vertical;
    double 			start_angle;
	double 			ray_dis;
	double 			dis; // distence to projection plan
	double 			wallhight;
	double 			start_draw;
	double 			end_draw;
	int				map_y;
	int				map_x;
	double			hit_x;
	double			hit_y;
	bool			hit_door;
	bool			hit_door_open;
	t_vect 			door_coor;
	// t_vect 			door_coor_v;

}	t_data;


void    free_trash(t_list **trash);
void	check_argument(char **av, int ac, t_data *data);
int		is_texture(char *line);
int		is_color(char *line);
int 	is_empty(char *line);
t_map   read_map(char *file);
void    add_to_trash(void *add, t_list **trash);
void	ft_error(char *str);
char	**duplicate_map(char **map);
int		count_coloumns(char **map);
void    free_map(char **map);
void	check_player(char **map);
t_data	*data_global();
void	get_postion(t_data *data, char **map);
bool	is_valid_number(char *str);
void	pars_the_color(t_data *data);
int		cont_character(char *str, int c);
// -----------------------------------
void	main_of_drawing(t_data *data);
int		rgb_to_hex(int r, int g, int b);
int		exit_key(void	*data);
int		move(void *parm);
void	ft_pixelput(t_img *img, int x, int y, int color);
int key_release(int key, void *parm);
int key_press(int key, void *parm);
void    render_3d(t_data *data);

void initialize_variables(t_data *data);
bool	check_if_surrounded(char **map);
void pars_texture(t_data *data);
int    get_x_max(char **map);
void minimap(t_data *data);
#endif
