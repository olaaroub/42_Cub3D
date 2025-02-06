/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 03:20:28 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/06 03:47:39 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_valid_move(t_data *data, double end_x, double end_y)
{
	t_vect	next;
	t_vect	grid;
	t_vect	grid_plus;
	t_vect	grid_minus;
	char	**map;

	next.x = data->player.x + end_x;
	next.y = data->player.y + end_y;
	map = data->map->map;
	grid.y = (int)data->player.y / SOF;
	grid_plus.x = (int)(next.x + 2) / SOF;
	grid_minus.x = (int)(next.x - 2) / SOF;
	if (!IS_BLOCKING_TILE(map[(int)grid.y][(int)grid_plus.x]) &&
		!IS_BLOCKING_TILE(map[(int)grid.y][(int)grid_minus.x]))
		data->player.x = next.x;
	grid.x = (int)data->player.x / SOF;
	grid_plus.y = (int)(next.y + 2) / SOF;
	grid_minus.y = (int)(next.y - 2) / SOF;
	if (!IS_BLOCKING_TILE(map[(int)grid_plus.y][(int)grid.x]) &&
		!IS_BLOCKING_TILE(map[(int)grid_minus.y][(int)grid.x]))
		data->player.y = next.y;
}

void	move_up(t_data *data)
{
	double	end_x;
	double	end_y;

	end_x = FRM * cos(data->angle) * SPEED;
	end_y = FRM * sin(data->angle) * SPEED;
	is_valid_move(data, end_x, end_y);
}

void	move_down(t_data *data)
{
	double	end_x;
	double	end_y;

	end_x = FRM * cos(data->angle + PI) * SPEED;
	end_y = FRM * sin(data->angle + PI) * SPEED;
	is_valid_move(data, end_x, end_y);
}

void	move_left(t_data *data)
{
	double	end_x;
	double	end_y;

	end_x = FRM * cos(data->angle - PI / 2) * SPEED;
	end_y = FRM * sin(data->angle - PI / 2) * SPEED;
	is_valid_move(data, end_x, end_y);
}

void	move_right(t_data *data)
{
	double	end_x;
	double	end_y;

	end_x = FRM * cos(data->angle + PI / 2) * SPEED;
	end_y = FRM * sin(data->angle + PI / 2) * SPEED;
	is_valid_move(data, end_x, end_y);
}
