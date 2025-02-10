/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:32:39 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/10 01:24:43 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	drawing1(t_data *data, int x, int y, int color)
{
	int	i;
	int	x_max;
	int	y_max;

	x_max = x + data->minimap->offset;
	y_max = y + data->minimap->offset;
	i = x;
	while (y < y_max)
	{
		x = i;
		while (x < x_max)
		{
			ft_pixelput(data->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	drawing_player(t_data *data, int x, int y)
{
	int	i;
	int	x_max;
	int	y_max;
	int	h;
	int	k;

	x_max = x + 20;
	y_max = y + 20;
	k = y + 10;
	h = x + 10;
	i = x;
	while (y < y_max)
	{
		x = i;
		while (x < x_max)
		{
			if (pow(x - h, 2) + pow(y - k, 2) <= pow(8, 2))
				ft_pixelput(data->img, x, y, 0xD4BEE4);
			x++;
		}
		y++;
	}
}

void	draw_square(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	data->minimap->offset = MI_SIZE;
	while (y <= 10)
	{
		x = 0;
		while (x <= 10)
		{
			drawing1(data, x * MI_SIZE, y * MI_SIZE, 0x0605678);
			x++;
		}
		y++;
	}
}

void	draw_element(t_data *data, int x_draw, int y_draw)
{
	char	**map;

	map = data->map->map;
	while (data->minimap->map_x <= (data->player.x / SOF) + 5
		&& map[(int)data->minimap->map_y][(int)data->minimap->map_x])
	{
		data->minimap->offset = MI_SIZE;
		if (map[data->minimap->map_y][data->minimap->map_x] == '1')
			drawing1(data, x_draw * MI_SIZE, y_draw * MI_SIZE, 0x09122C);
		else if (map[data->minimap->map_y][data->minimap->map_x] == 'D')
			drawing1(data, x_draw * MI_SIZE, y_draw * MI_SIZE, 0x6D2323);
		else if (map[data->minimap->map_y][data->minimap->map_x] == 'F')
			drawing1(data, x_draw * MI_SIZE, y_draw * MI_SIZE, 0x09122C);
		else if (map[data->minimap->map_y][data->minimap->map_x] == 'O')
			drawing1(data, x_draw * MI_SIZE, y_draw * MI_SIZE, 0xA31D1D);
		else if (map[data->minimap->map_y][data->minimap->map_x] != ' ')
			drawing1(data, x_draw * MI_SIZE, y_draw * MI_SIZE, 0x872341);
		get_position_of_player_in_minimap(data, x_draw, y_draw);
		data->minimap->map_x++;
		x_draw++;
	}
}

// void	minimap(t_data *data)
// {
// 	int	x_draw;
// 	int	y_draw;

// 	y_draw = 0;
// 	data->minimap->flag = false;
// 	data->minimap->map_y = (data->player.y / SOF) - 5;
// 	draw_square(data);
// 	if (data->minimap->map_y < 0)
// 		data->minimap->map_y = 0;
// 	while (data->minimap->map_y <= (data->player.y / SOF) + 5
// 		&& data->map->map[(int)data->minimap->map_y])
// 	{
// 		data->minimap->map_x = (data->player.x / SOF) - 5;
// 		x_draw = 0;
// 		if (data->minimap->map_x < 0)
// 			data->minimap->map_x = 0;
// 		draw_element(data, x_draw, y_draw);
// 		y_draw++;
// 		data->minimap->map_y++;
// 	}
// 	drawing_player(data, data->minimap->player.x, data->minimap->player.y);
// }

t_vect	inverse_rotate(int x, int y, t_data *data, int offset)
{
	t_vect	p;
	double	translated_x;
	double	translated_y;

	translated_x = x - offset;
	translated_y = y - (SCREEN_H - offset);
	p.x = translated_x * cos(data->minimap->rot_angle) - translated_y
		* sin(data->minimap->rot_angle);
	p.y = translated_x * sin(data->minimap->rot_angle) + translated_y
		* cos(data->minimap->rot_angle);
	return (p);
}

void drawthepixels()
{

}

void	minimap_draw(t_data *data, char **map)
{
	int		offset;
	t_vect	src;
	int		grid_x;
	int		grid_y;
	int		dest_y;
	int		dest_x;

	offset = data->minimap->len;
	dest_y = SCREEN_H - offset * 2 - 10;
	data->minimap->rot_angle = data->angle + PI / 2;
	while (dest_y < SCREEN_H)
	{
		dest_x = 0;
		while (dest_x < offset * 2)
		{
			src = inverse_rotate(dest_x, dest_y, data, offset);
			grid_x = floor((src.x + data->minimap->player.x) / MI_SIZE);
			grid_y = floor((src.y + data->minimap->player.y) / MI_SIZE);
			if (pow(dest_x - data->minimap->circle_center.x, 2) + pow(dest_y
					- data->minimap->circle_center.y, 2) <= pow(offset, 2))
			{
				if (grid_x >= 0 && grid_y >= 0 && grid_y < data->y_max
					&& grid_x < (int)ft_strlen(map[grid_y]))
				{
					if (map[grid_y][grid_x] == '1')
						ft_pixelput(data->img, dest_x, dest_y, 0x09122C);
					else if (map[grid_y][grid_x] == 'D')
						ft_pixelput(data->img, dest_x, dest_y, 0x6D2323);
					else if (map[grid_y][grid_x] == 'O')
						ft_pixelput(data->img, dest_x, dest_y, 0xA31D1D);
					else if (map[grid_y][grid_x] == 'F')
						ft_pixelput(data->img, dest_x, dest_y, 0x09122C);
					else if (map[grid_y][grid_x] != ' ')
						ft_pixelput(data->img, dest_x, dest_y, 0x872341);
					else
						ft_pixelput(data->img, dest_x, dest_y, 0x872341);
				}
				else
					ft_pixelput(data->img, dest_x, dest_y, 0x872341);
			}
			dest_x++;
		}
		dest_y++;
	}
}

void	minimap(t_data *data)
{
	data->minimap->len = MI_SIZE * 5;
	data->minimap->circle_center.x = data->minimap->len;
	data->minimap->circle_center.y = SCREEN_H - data->minimap->len;
	data->minimap->flag = false;
	data->minimap->player.x = (data->player.x / SOF) * MI_SIZE;
	data->minimap->player.y = (data->player.y / SOF) * MI_SIZE;
	minimap_draw(data, data->map->map);
	drawing_player(data, data->minimap->circle_center.x - 10,
		data->minimap->circle_center.y - 10);
}
