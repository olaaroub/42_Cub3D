/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:32:39 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/23 15:05:03 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	drawing1(t_img *img, int x, int y, int color)
// {
// 	int i;
// 	int x_max;
// 	int y_max;

// 	x_max =  x + data->offset;
// 	y_max = y + data_global()->offset;
// 	i = x;
// 	while (y < y_max)
// 	{
// 		x = i;
// 		while(x < x_max)
// 		{
// 			ft_pixelput(img, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	drawing_player(t_img *img, int x, int y)
// {
// 	data_global()->offset = 10;
// 	drawing1(img, x, y, 0xfcba03);

// }

// void	minimap(t_img *img, t_data *data)
// {
// 	int	x;
// 	int	y;
// 	int x_draw;
// 	int y_draw;

// 	y_draw = 0;
// 	y = (data->player_y / SOF) - 5;
// 	if (y < 0)
// 		y = 0;
// 	while (y <= (data->player_y / SOF) + 5 && data->map.map[y])
// 	{
// 		x = (data->player_x / SOF) - 5;
// 		x_draw = 0;
// 		if (x < 0)
// 			x = 0;
// 		while(x <= (data->player_x / SOF) + 5 && data->map.map[y][x])
// 		{
// 			data->offset = MI_SIZE;
// 			if (data->map.map[y][x] == '1')
// 				drawing1(img, x_draw * MI_SIZE, y_draw * MI_SIZE, 0xFFFFFF);
// 			else if (data->map.map[y][x] != ' ')
// 				drawing1(img, x_draw * MI_SIZE, y_draw * MI_SIZE, 0xFF0000);
// 			if (x == (int)data->player_x / SOF && y == (int)data->player_y / SOF)
// 				drawing_player(img, x_draw * MI_SIZE, y_draw * MI_SIZE);
// 			x++;
// 			x_draw++;
// 		}
// 		y_draw++;
// 		y++;
// 	}
// }

void minimap_draw(t_img *img, t_data *data, char **map)
{
	data->minimap.i = (int)(data->minimap.x_start / SOF);
	data->minimap.j = (int)(data->minimap.y_start / SOF);
	if (data->minimap.i < 0)
		data->minimap.i = 0;
	if (data->minimap.j < 0)
		data->minimap.j = 0;

	if (data->minimap.j >= count_coloumns(map))
		data->minimap.j = count_coloumns(map) - 1;
	if (data->minimap.i > (int)ft_strlen(map[0]))
		data->minimap.i = (int)ft_strlen(map[0]) - 1;
	int offset = data->minimap.len + 20;
	double angle = data->angle - (PI / 2);
	int rotx = round(data->minimap.x * cos(angle) - data->minimap.y * sin(angle)) + offset;
	int roty = round(data->minimap.x * sin(angle) + data->minimap.y * cos(angle)) + SCREEN_H - offset;

	if (map[data->minimap.j][data->minimap.i] && map[data->minimap.j][data->minimap.i] == '1')
		ft_pixelput(img, rotx , roty, 0xFFFFFF);
	else if (data->minimap.i == (int)((data->player_x) / SOF) && data->minimap.j == (int)(data->player_y / SOF))
		ft_pixelput(img, rotx, roty, 0xfcba03);
	else if (map[data->minimap.j][data->minimap.i] && map[data->minimap.j][data->minimap.i] == '0')
		ft_pixelput(img, rotx, roty, 0xFF0000);
	else
		ft_pixelput(img, rotx, roty, 0xE8F9FF);
}

void minimap(t_img *img, t_data *data)
{
	data->minimap.len = MI_SIZE * 5;
	data->minimap.y_start = data->player_y - data->minimap.len;
	data->minimap.x_end = data->player_x + data->minimap.len;
	data->minimap.y_end = data->player_y + data->minimap.len;
	data->minimap.y = -data->minimap.len;
	char **map = data->map.map;
	while (data->minimap.y_start < data->minimap.y_end)
	{
		data->minimap.x = -data->minimap.len;
		data->minimap.x_start = data->player_x - data->minimap.len;
		while (data->minimap.x_start < data->minimap.x_end)
		{
			if (pow(data->minimap.x_start - data->player_x, 2) + pow(data->minimap.y_start - data->player_y, 2) <= pow(data->minimap.len, 2))
				minimap_draw(img, data, map);
			data->minimap.x_start++;
			data->minimap.x++;
		}
		data->minimap.y++;
		data->minimap.y_start++;
	}
}
