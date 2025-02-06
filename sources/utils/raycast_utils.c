/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 01:09:24 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/06 03:50:51 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	horizontal_intersection(t_data *data, t_vect *hit)
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	x;
	double	y;

	x = data->player.x;
	y = data->player.y;
	ray_dir_x = cos(data->start_angle);
	ray_dir_y = sin(data->start_angle);
	if (ray_dir_y < 0)
		hit->y = floor(y / SOF) * SOF - EPSILON;
	else
		hit->y = floor(y / SOF) * SOF + SOF;
	hit->x = x + ((hit->y - y) / ray_dir_y) * ray_dir_x;
}

void	vertical_intersection(t_data *data, t_vect *hit)
{
	t_vect	ray_dir;
	double	x;
	double	y;

	x = data->player.x;
	y = data->player.y;
	ray_dir.x = cos(data->start_angle);
	ray_dir.y = sin(data->start_angle);
	if (ray_dir.x < 0)
		hit->x = floor(x / SOF) * SOF - EPSILON;
	else
		hit->x = floor(x / SOF) * SOF + SOF;
	hit->y = y + ((hit->x - x) / ray_dir.x) * ray_dir.y;
}

int	hit_tile_v(t_data *data, t_raycast_vars *vars)
{
	if (vars->map.y >= 0 && vars->map.y < data->y_max && vars->map.x >= 0
		&& vars->map.x < (int)ft_strlen(data->map->map[(int)vars->map.y]))
	{
		if (data->map->map[(int)vars->map.y][(int)vars->map.x] == '1'
			|| ((data->map->map[(int)vars->map.y][(int)vars->map.x] == 'D'
					|| data->map->map[(int)vars->map.y][(int)vars->map.x] == 'O'
				|| data->map->map[(int)vars->map.y][(int)vars->map.x] == 'F')
				&& BONUS == 1))
		{
			if (data->map->map[(int)vars->map.y][(int)vars->map.x] == 'D')
				vars->hit_door_v = true;
			else if (data->map->map[(int)vars->map.y][(int)vars->map.x] == 'O')
				vars->hit_door_ov = true;
			else if (data->map->map[(int)vars->map.y][(int)vars->map.x] == 'F')
				vars->hit_fire_v = true;
			return (69);
		}
		return (-1);
	}
	return (0);
}

int	hit_tile_h(t_data *data, t_raycast_vars *vars)
{
	if (vars->map.y >= 0 && vars->map.y < data->y_max && vars->map.x >= 0
		&& vars->map.x < (int)ft_strlen(data->map->map[(int)vars->map.y])
		&& (data->map->map[(int)vars->map.y][(int)vars->map.x] == '1'
		|| ((data->map->map[(int)vars->map.y][(int)vars->map.x] == 'D'
			|| data->map->map[(int)vars->map.y][(int)vars->map.x] == 'O'
		|| data->map->map[(int)vars->map.y][(int)vars->map.x] == 'F')
				&& BONUS == 1)))
	{
		if (data->map->map[(int)vars->map.y][(int)vars->map.x] == 'D')
			vars->hit_door_h = true;
		else if (data->map->map[(int)vars->map.y][(int)vars->map.x] == 'O')
			vars->hit_door_oh = true;
		else if (data->map->map[(int)vars->map.y][(int)vars->map.x] == 'F')
			vars->hit_fire_h = true;
		return (69);
	}
	return (0);
}
