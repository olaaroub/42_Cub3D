/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:24:51 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/07 18:51:07 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_postion(t_data *data, char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'E'
				|| map[j][i] == 'W')
			{
				data->player.x = i;
				data->player.y = j;
				return ;
			}
			i++;
		}
		j++;
	}
}

static void	initialize_the_angle(t_data *data)
{
	char	**map;

	map = data->map->map;
	if (map[(int)data->player.y][(int)data->player.x] == 'E')
		data->angle = 0;
	else if (map[(int)data->player.y][(int)data->player.x] == 'W')
		data->angle = PI;
	else if (map[(int)data->player.y][(int)data->player.x] == 'N')
		data->angle = 3 * PI / 2;
	else if (map[(int)data->player.y][(int)data->player.x] == 'S')
		data->angle = PI / 2;
}

void	initialize_variables(t_data *data)
{
	initialize_the_angle(data);
	data->anim = malloc(sizeof(t_animations));
	data->vars_h = malloc(sizeof(t_raycast_vars));
	data->vars_v = malloc(sizeof(t_raycast_vars));
	if (!data->anim || !data->vars_h || !data->vars_v)
		ft_error(data, "Error:\nMalloc failed\n", 1);
	add_to_trash(&data->trash, data->vars_h);
	add_to_trash(&data->trash, data->vars_v);
	add_to_trash(&data->trash, data->anim);
	data->player.x = (data->player.x * SOF) + SOF / 3;
	data->player.y = (data->player.y * SOF) + SOF / 3;
	ft_memset((void *)&data->moves, 0, sizeof(t_moves));
	ft_memset((void *)data->anim, 0, sizeof(t_animations));
	data->hit_door = false;
	data->hit_open_door = false;
	data->projection_dist = (SCREEN_W / 2) / tan(FOV_ANGLE / 2);
}
