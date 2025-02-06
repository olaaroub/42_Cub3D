/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 03:17:48 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/06 03:41:56 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_door(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->map[y] && y < data->y_max)
	{
		x = 0;
		while (data->map->map[y][x] && x < data->x_max)
		{
			if (data->map->map[y][x] == 'D' && data->moves.opened == false)
				data->map->map[y][x] = 'O';
			x++;
		}
		y++;
	}
	data->moves.opened = true;
}

void	close_door(t_data *data)
{
	int	x;
	int	y;
	int	player_x;
	int	player_y;

	player_x = (int)data->player.x / SOF;
	player_y = (int)data->player.y / SOF;
	y = 0;
	if (data->map->map[player_y][player_x] == 'O')
		return ;
	while (data->map->map[y] && y < data->y_max)
	{
		x = 0;
		while (data->map->map[y][x] && x < data->x_max)
		{
			if ((data->map->map[y][x] == 'O') && data->moves.opened == true)
				data->map->map[y][x] = 'D';
			x++;
		}
		y++;
	}
	data->moves.opened = false;
}
