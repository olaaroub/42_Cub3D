/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:32:59 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/29 02:04:51 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	exit_key(void *param)
{
	t_data *data;

	data= (t_data *)param;
	mlx_destroy_image(data->mlx, data->img->img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

void initialize_the_angle(t_data *data)
{
	char **map;

	map = data->map.map;
	if (map[(int)data->player_y][(int)data->player_x] == 'E')
		data->angle = 0;
	else if (map[(int)data->player_y][(int)data->player_x] == 'W')
		data->angle = PI;
	else if (map[(int)data->player_y][(int)data->player_x] == 'N')
		data->angle = PI / 2;
	else if (map[(int)data->player_y][(int)data->player_x] == 'S')
		data->angle = 3 * PI / 2;
}

void initialize_variables(t_data *data)
{
	initialize_the_angle(data);
	data->player_x = (data->player_x * SOF) + SOF / 3;
	data->player_y = (data->player_y * SOF) + SOF / 3;
    data->d_pressed = 0;
	data->a_pressed = 0;
    data->w_pressed = 0;
	data->s_pressed = 0;
    data->turn_left = 0;
    data->turn_right = 0;
	data->is_vertical = false;
	data->hit_door = false;
	data->hit_door_open = false;
}

void	main_of_drawing(t_data *data)
{
	render_3d(data);
	mlx_hook(data->mlx_win, DestroyNotify, StructureNotifyMask,exit_key, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, key_press, data);
	mlx_loop_hook(data->mlx, move, data);
}


