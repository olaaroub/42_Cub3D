/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:32:59 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/03 00:59:06 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	map = data->map->map;
	if (map[(int)data->player.y][(int)data->player.x] == 'E')
		data->angle = 0;
	else if (map[(int)data->player.y][(int)data->player.x] == 'W')
		data->angle = PI;
	else if (map[(int)data->player.y][(int)data->player.x] == 'N')
		data->angle = PI / 2;
	else if (map[(int)data->player.y][(int)data->player.x] == 'S')
		data->angle = 3 * PI / 2;
}

void initialize_variables(t_data *data)
{
	initialize_the_angle(data);
	data->animations = malloc(sizeof(t_animations));
	if (!data->animations)
		ft_error("Error: Malloc failed");
	data->player.x = (data->player.x * SOF) + SOF / 3;
	data->player.y = (data->player.y * SOF) + SOF / 3;
    data->moves.d_pressed = 0;
	data->moves.a_pressed = 0;
    data->moves.w_pressed = 0;
	data->moves.s_pressed = 0;
    data->moves.turn_left = 0;
    data->moves.turn_right = 0;
	data->is_vertical = false;
	data->hit_door = false;
	data->moves.opened = false;
	data->hit_open_door = false;
	data->animations->fire_switch = false;
	FRAMES = 0;
	HAND_CURR_FRAME = 0;
	FIRE_CURR_FRAME = 0;
}

void	main_of_drawing(t_data *data)
{
	render_3d(data);
	mlx_hook(data->mlx_win, DestroyNotify, StructureNotifyMask, exit_key, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_loop_hook(data->mlx, move, data);
}


