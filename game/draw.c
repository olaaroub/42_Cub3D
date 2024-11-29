/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:32:39 by ohammou-          #+#    #+#             */
/*   Updated: 2024/10/10 21:03:00 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	open_the_window()
{
	data_global()->mlx = mlx_init();
	data_global()->mlx_win = mlx_new_window(data_global()->mlx, data_global()->x_max * 60,
			data_global()->y_max * 60, "window");
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

	x_max = x + data_global()->offset;
	y_max = y + data_global()->offset;
	i = x;
	while (y < y_max - 3)
	{
		x = i;
		while(x < x_max - 3)
		{
			ft_pixelput(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	drawing_player(t_img *img)
{
	int	i;

	data_global()->offset = 20;
	drawing1(img, data_global()->x, data_global()->y, 0xfcba03);
	
}

int	drawing()
{
	t_img img;
	int	x;
	int	y;

	y = 0;
	get_data_addr(&img);
	while (data_global()->map.map[y])
	{
		x = 0;
		while(data_global()->map.map[y][x])
		{
			data_global()->offset = 60;
			if (data_global()->map.map[y][x] == '1')
				drawing1(&img, x * 60, y * 60, 0xFFFFFF);
			else if (data_global()->map.map[y][x] != ' ')
				drawing1(&img, x * 60, y * 60, 0xFF0000);
			x++;
		}
		y++;
	}
	drawing_player(&img);
	put_and_destroy_img(&img);
	return 0;
}

