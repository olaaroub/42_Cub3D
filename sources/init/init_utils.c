/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:24:51 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/03 18:18:05 by olaaroub         ###   ########.fr       */
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
		   if (map[j][i] == 'N' || map[j][i] == 'S'
			|| map[j][i] == 'E' || map[j][i] == 'W')
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

static void initialize_the_angle(t_data *data)
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
	data->vars_h = malloc(sizeof(t_raycast_vars));
	data->vars_v = malloc(sizeof(t_raycast_vars));
	if (!data->animations || !data->vars_h || !data->vars_v)
		ft_error("Error: Malloc failed");
	data->player.x = (data->player.x * SOF) + SOF / 3;
	data->player.y = (data->player.y * SOF) + SOF / 3;
    data->moves.d_pressed = 0;
	data->moves.a_pressed = 0;
    data->moves.w_pressed = 0;
	data->moves.s_pressed = 0;
    data->moves.turn_left = 0;
    data->moves.turn_right = 0;
	data->hit_door = false;
	data->moves.opened = false;
	data->hit_open_door = false;
	data->animations->fire_switch = false;
	data->field_of_view = PI / 3;
	data->two_pi = PI * 2;
	data->projection_dist = (SCREEN_W / 2) / tan(FOV_ANGLE / 2);
	FRAMES = 0;
	HAND_CURR_FRAME = 0;
	FIRE_CURR_FRAME = 0;
}

int count_coloumns(char **map)
{
    int len;

    len = 0;
    while (map[len])
        len++;
    return (len);
}