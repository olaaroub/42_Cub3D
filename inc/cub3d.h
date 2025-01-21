/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:51:20 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/21 19:59:53 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
#define CUB3D_H

#include "../minilibx-linux/mlx.h"
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
#define ROT_SPEED 0.1
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
	char *textur_as_lien;
	char *map_as_lien;
	int  ceiling_hex;
	int  floor_hex;
	int  flag;

	char *texturOfWe;
	char *texturOfSo;
	char *texturOfNo;
	char *texturOfEa;
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

typedef struct s_data
{
	t_texture		*north_tex;
	t_texture		*south_tex;
	t_texture		*west_tex;
	t_texture		*east_tex;
	int *texture;
	int *south;
	int *east;
	int *west;
	void			*mlx;
	void			*mlx_win;
	double			x;
	double			y;
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
	t_img			*img;
	int				offset;
	double			angle;
	int				fg_left;
	int				fg_right;
	int				fg_W;
	int				fg_E;
	int				fg_N;
	int				fg_S;
	double			dh; // destance for horizontal
	double			dv; // destance for vertical;
	// -------rander 3d--------
    double 			angle_step;
	bool			is_vertical;
    double 			start_angle;
	double 			ray_dis;
	double 			dis; // distence to projection plan
	double 			wallhight;
	double 			start_draw;
	double 			end_draw;
	int				map_y;
	int				map_x;
	// ------ mini map------
	int				len;
	double			x_end;
	double			y_end;
	int				dx;
	int				dy;
	int				steps;
	double			x_inc;
	double 			y_inc;
	double			x_start;
	double			y_start;
	//-------------------------
	double			hit_x;
	double			hit_y;
}	t_data;


void	check_argument(char **av, int ac);
int		is_texture(char *line);
int		is_color(char *line);
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
bool	is_valid_number(char *str);
void	pars_the_color(t_data *data);
int		cont_character(char *str, int c);
// -----------------------------------
void	main_of_drawing(t_data *data);
int    rgb_to_hex(int r, int g, int b);
int		krwa();
void	open_the_window();
int		drawing(t_data *data);
int		move(void *parm);
void	get_data_addr(t_img *img);
void 	put_img(t_img *img);
int 	drawing_ray(t_img *img, double angle, int ray_length);
void	ft_pixelput(t_img *img, int x, int y, int color);
int key_release(int key, void *parm);
void drawing_rays(t_img *img);
int key_press(int key, void *parm);
void    render_3d(t_data *data);
void	minimap(t_img *img);

void	initialize_variables(t_data *data);
bool	check_mapifitSurrounded(char **map);
void	pars_texture(t_data *data);
#endif
