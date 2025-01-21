/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:32:59 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/21 18:12:05 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
}


void	main_of_drawing(t_data *data)
{
	// drawing(img);
	render_3d(data);
	mlx_hook(data->mlx_win, 17, 0,exit_key, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_press, data);
	mlx_loop_hook(data->mlx, move, data);
}


