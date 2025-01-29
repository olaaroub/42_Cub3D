/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:32:39 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/29 20:55:22 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	drawing1(t_data *data, int x, int y, int color)
{
	int i;
	int x_max;
	int y_max;

	x_max =  x + data->offset;
	y_max = y + data->offset;
	i = x;
	while (y < y_max)
	{
		x = i;
		while(x < x_max)
		{
			ft_pixelput(data->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	drawing_player(t_data*data, int x, int y)
{
	int i;
	int x_max;
	int y_max;
	int h;
	int k;

	x_max =  x + 20;
	y_max = y + 20;
	k = y + 10;
	h = x + 10;
	i = x;
	while (y < y_max)
	{
		x = i;
		while(x < x_max)
		{
			if (pow(x - h, 2) + pow(y - k, 2) <= pow(8, 2))
				ft_pixelput(data->img, x, y, 0xD4BEE4);
			x++;
		}
		y++;
	}

}

void draw_square(t_data *data)
{
	int x;
	int y;

	y = 0;
	data->offset = MI_SIZE;
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

void	minimap1(t_data *data)
{
	int	x;
	int	y;
	int x_draw;
	int y_draw;
    double player_x;
    double player_y;

	y_draw = 0;
	y = (data->player_y / SOF) - 5;
	draw_square(data);
	if (y < 0)
		y = 0;
	while (y <= (data->player_y / SOF) + 5 && data->map.map[y])
	{
		x = (data->player_x / SOF) - 5;
		x_draw = 0;
		if (x < 0)
			x = 0;
		while(x <= (data->player_x / SOF) + 5 && data->map.map[y][x])
		{
			data->offset = MI_SIZE;
			if (data->map.map[y][x] == '1')
				drawing1(data, x_draw * MI_SIZE, y_draw * MI_SIZE, 0x3B1E54);
			else if (data->map.map[y][x] == 'D')
				drawing1(data, x_draw * MI_SIZE, y_draw * MI_SIZE, 0x2A004E);
			else if (data->map.map[y][x] == 'O')
				drawing1(data, x_draw * MI_SIZE, y_draw * MI_SIZE, 0x500073);
			else if (data->map.map[y][x] != ' ')
				drawing1(data, x_draw * MI_SIZE, y_draw * MI_SIZE, 0x9B7EBD);
			if (x == (int)data->player_x / SOF && y == (int)data->player_y / SOF)
            {
                player_x = ((x_draw + fabs(data->player_x / SOF - x)) * MI_SIZE) - 10;
                player_y = ((y_draw + fabs(data->player_y / SOF - y)) * MI_SIZE) - 10;
            }
			x++;
			x_draw++;
		}
		y_draw++;
		y++;
	}
	drawing_player(data, player_x, player_y);
}

void player_drawing(t_data *data)
{
    int rotx;
    int roty;
    int offset;
    int i;
    int j;
	double angle = -data->angle - PI / 2;
	if (angle < 0)
        angle += 2 * PI;
    j = 0;
    offset = data->minimap.len + 20;
    while (j < 10)
    {
        i = 0;
        while (i < 10)
        {
            rotx = round((data->minimap.tmp_x + i) * cos(angle) - (data->minimap.tmp_y + j) * sin(angle)) + offset;
            roty = round((data->minimap.tmp_x + i) * sin(angle) + (data->minimap.tmp_y +j) * cos(angle)) + SCREEN_H - offset;
			// printf("%f  %f  %d\n", (data->minimap.tmp_x + i) * cos(angle) - (data->minimap.tmp_y + j) * sin(angle), (data->minimap.tmp_x + i) * sin(angle) + (data->minimap.tmp_y +j) * cos(angle) + SCREEN_H - offset, roty);
			// if (roty != (int)((data->minimap.tmp_x + i) * sin(angle) + (data->minimap.tmp_y +j) * cos(angle)) + SCREEN_H - offset)
			// 	ft_error("not e\n");
            ft_pixelput(data->img, rotx, roty, 0xfcba03);
            i++;
        }
        j++;
    }
}

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
	if (data->minimap.i >= (int)ft_strlen(map[0]))
		data->minimap.i = (int)ft_strlen(map[0]) - 1;
	int offset = data->minimap.len + 20;
	double angle = -data->angle - PI / 2;
	if (angle < 0)
        angle += 2 * PI;
	int rotx = (int)(data->minimap.x * cos(angle) - data->minimap.y * sin(angle)) + offset;
	int roty = (int)(data->minimap.x * sin(angle) + data->minimap.y * cos(angle)) + SCREEN_H - offset;
	// printf("%f %f\n", (data->minimap.x * cos(angle) - data->minimap.y * sin(angle)) + offset,(data->minimap.x * sin(angle) + data->minimap.y * cos(angle)) + SCREEN_H - offset);
	if (map[data->minimap.j][data->minimap.i] && map[data->minimap.j][data->minimap.i] == '1')
		ft_pixelput(img, rotx , roty, 0xFFFFFF);
	else if (data->minimap.i == (int)((data->player_x) / SOF) && data->minimap.j == (int)(data->player_y / SOF))
	{
		if (!data->minimap.flag)
		{
			data->minimap.tmp_x = data->minimap.x + fabs((data->player_x / SOF) - data->minimap.i) * SOF;
			data->minimap.tmp_y = data->minimap.y + fabs((data->player_y / SOF) - data->minimap.j) * SOF;
		}
        ft_pixelput(img, rotx, roty, 0xFF0000);
        data->minimap.flag = 1;
    }
	else if (map[data->minimap.j][data->minimap.i] && map[data->minimap.j][data->minimap.i] == 'D')
		ft_pixelput(img, rotx, roty, 0x000957);
	else if (map[data->minimap.j][data->minimap.i] && map[data->minimap.j][data->minimap.i] != ' ')
		ft_pixelput(img, rotx, roty, 0xFF0000);
	else
		ft_pixelput(img, rotx, roty, 0xE8F9FF);
}

void minimap(t_data *data)
{
// 	data->minimap.len = MI_SIZE * 5;
// 	data->minimap.y_start = data->player_y - data->minimap.len;
// 	data->minimap.x_end = data->player_x + data->minimap.len;
// 	data->minimap.y_end = data->player_y + data->minimap.len;
// 	data->minimap.y = -data->minimap.len;
// 	data->minimap.flag = 0;
// 	char **map = data->map.map;
// 	while (data->minimap.y_start < data->minimap.y_end)
// 	{
// 		data->minimap.x = -data->minimap.len;
// 		data->minimap.x_start = data->player_x - data->minimap.len;
// 		while (data->minimap.x_start < data->minimap.x_end)
// 		{
// 			if (pow(data->minimap.x_start - data->player_x, 2) + pow(data->minimap.y_start - data->player_y, 2) <= pow(data->minimap.len, 2))
// 				minimap_draw(data->img, data, map);
// 			data->minimap.x_start++;
// 			data->minimap.x++;
// 		}
// 		data->minimap.y++;
// 		data->minimap.y_start++;
// 	}
    // player_drawing(data);

	minimap1(data);
}