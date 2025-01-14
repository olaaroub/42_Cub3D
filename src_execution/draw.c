/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:32:39 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/14 19:01:31 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	open_the_window()
{
	data_global()->mlx = mlx_init();
	data_global()->mlx_win = mlx_new_window(data_global()->mlx, SCREEN_W,
			SCREEN_H, "window");
}

void	ft_pixelput(t_img *img, int x, int y, int color)
{
	char	*tmp;

	tmp = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)tmp = color;
}

void	drawing1(t_img *img, int x, int y, int color)
{
	int i;
	int x_max;
	int y_max;

	x_max =  x + data_global()->offset;
	y_max = y + data_global()->offset;
	i = x;
	while (y < y_max)
	{
		x = i;
		while(x < x_max)
		{
			ft_pixelput(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	drawing_player(t_img *img, int x, int y)
{
	data_global()->offset = 30;
	drawing1(img, x, y, 0xfcba03);

}

// void	minimap(t_img *img)
// {
// 	int	x;
// 	int	y;
// 	int x_draw;
// 	int y_draw;

// 	y_draw = 0;
// 	y = (data_global()->y / SOF) - 5;
// 	if (y < 0)
// 		y = 0;
// 	while (y <= (data_global()->y / SOF) + 5 && data_global()->map.map[y])
// 	{
// 		x = (data_global()->x / SOF) - 5;
// 		x_draw = 0;
// 		if (x < 0)
// 			x = 0;
// 		while(x <= (data_global()->x / SOF) + 5 && data_global()->map.map[y][x])
// 		{
// 			data_global()->offset = MI_SIZE;
// 			if (data_global()->map.map[y][x] == '1')
// 				drawing1(img, x_draw * MI_SIZE, y_draw * MI_SIZE, 0xFFFFFF);
// 			else if (data_global()->map.map[y][x] != ' ')
// 				drawing1(img, x_draw * MI_SIZE, y_draw * MI_SIZE, 0xFF0000);
// 			if (x == (int)data_global()->x / SOF && y == (int)data_global()->y / SOF)
// 				drawing_player(img, x_draw * MI_SIZE, y_draw * MI_SIZE);	
// 			x++;
// 			x_draw++;
// 		}
// 		y_draw++;
// 		y++;
// 	}
// }

void minimap_draw(t_img *img, t_data data, char **map)
{
	data.i = data.x_start / SOF;
	data.j = data.y_start / SOF;
	if (data.i < 0)
		data.i = 0;
	if (data.j < 0)
		data.j = 0;
	if (data.x < SCREEN_W && data.x >= 0 && data.y < SCREEN_H && data.y >= 0)
	{
		if (map[data.j][data.i] == '1')
			ft_pixelput(img, data.x, data.y, 0xFFFFFF);
		else if (map[data.j][data.i] == '0')
			ft_pixelput(img, data.x, data.y, 0xFF0000);
		else
			ft_pixelput(img, data.x, data.y, 0xE8F9FF);
	}	
}

void minimap(t_img *img)
{
	t_data data;

	data.len = MI_SIZE * 5;
	data.y_start = data_global()->y - data.len;
	data.x_end = data_global()->x + data.len;
	data.y_end = data_global()->y + data.len;
	data.y = SCREEN_H - (data.y_end - data.y_start) - 20;
	char **map = data_global()->map.map;
	while (data.y_start < data.y_end)
	{
		data.x = 20;
		data.x_start = data_global()->x - data.len;
		while (data.x_start < data.x_end)
		{
			if (pow(data.x_start - data_global()->x, 2) + pow(data.y_start - data_global()->y, 2) <= pow(data.len, 2))
			{
				minimap_draw(img, data, map);
			}
			data.x_start++;
			data.x++;
		}
		data.y++;
		data.y_start++;
	}
}
