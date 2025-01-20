/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:32:59 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/20 17:13:33 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void initialize_the_angle(t_data *data)
{
	char **map;

	map = data->map.map;
	if (map[data->j][data->i] == 'E')
		data->angle = 0;
	else if (map[data->j][data->i] == 'W')
		data->angle = PI;
	else if (map[data->j][data->i] == 'N')
		data->angle = PI / 2;
	else if (map[data->j][data->i] == 'S')
		data->angle = 3 * PI / 2;
}

void initialize_variables(t_data *data)
{
	data->i = data->x;
	data->j = data->y;
	data->x = (data->x * SOF) + SOF / 3;
	data->y = (data->y * SOF) + SOF / 3;

    data->fg_E = 0;
	data->fg_W = 0;
    data->fg_N = 0;
	data->fg_S = 0;

    data->fg_left = 0;
    data->fg_right = 0;
	data->is_vertical = false;
	data->texture = (int*)malloc(64 * 64 * 4);
	// data->south = (int*)malloc(64 * 64 * 4);
	// data->east = (int*)malloc(64 * 64 * 4);
	// data->west = (int*)malloc(64 * 64 * 4);
	int i = 0;
	int j = 0;

	while(i < 64)
	{
		j = 0;
		while(j < 64)
		{
			(data->texture)[(j * 64) + i] = (i % 8 && j % 8) ? 0xFF0000FF : 0xFF000000;
			// (data->texture)[(j * 64) + i] = (i % 8 && j % 8) ? 0xFFFFFF00 : 0xFF000000;
			// (data->east)[(j * 64) + i] = (i % 8 && j % 8) ? 0xFFFF0000 : 0xFF000000;
			// (data->west)[(j * 64) + i] = (i % 8 && j % 8) ? 0xFF00FF00 : 0xFF000000;
			j++;
		}
		i++;
	}
	initialize_the_angle(data);
}


void	main_of_drawing(t_data *data)
{
	// drawing(img);
	render_3d(data);
	mlx_hook(data->mlx_win, 17, 0,krwa, NULL);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_press, data);
	mlx_loop_hook(data->mlx, move, data);
}


