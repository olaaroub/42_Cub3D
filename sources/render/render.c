/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:32:59 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/11 01:12:55 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_hand(t_data *data)
{
	t_texture	*tex;
	t_vect		pos;
	int			color;
	int			i;
	int			j;

	i = 0;
	tex = data->anim->h_tex[data->anim->h_curr];
	pos.x = (SCREEN_W - tex->width) / 2;
	pos.y = SCREEN_H - tex->height + 10;
	while (i < tex->height)
	{
		j = 0;
		while (j < tex->width)
		{
			color = *(int *)(tex->addr + (i * tex->line_len + j * (tex->bpp
							/ 8)));
			if ((color & 0x00FFFFFF) != 0)
				ft_pixelput(data->img, pos.x + j, pos.y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_pixels(t_data *data, int x)
{
	int	y;
	int	color;

	y = 0;
	while (y < SCREEN_H)
	{
		while (y < data->start_draw)
			ft_pixelput(data->img, x, y++, data->map->ceiling_hex);
		while (y >= data->start_draw && y < data->end_draw)
		{
			if (data->is_vertical)
				color = get_vertical_color(data, y);
			else
				color = get_horizontal_color(data, y);
			ft_pixelput(data->img, x, y, color);
			y++;
		}
		ft_pixelput(data->img, x, y, data->map->floor_hex);
		y++;
	}
}

void	render(t_data *data)
{
	int		x;
	double	angle_step;

	angle_step = FOV_ANGLE / SCREEN_W;
	data->start_angle = data->angle - (FOV_ANGLE / 2);
	if (data->start_angle < 0)
		data->start_angle += TWO_PI;
	x = -1;
	while (++x < SCREEN_W)
	{
		raycast(data);
		draw_pixels(data, x);
		data->start_angle += angle_step;
	}
	if (BONUS == 1)
	{
		minimap(data);
		render_hand(data);
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}

void	game_loop(t_data *data)
{
	render(data);
	mlx_hook(data->mlx_win, DestroyNotify, StructureNotifyMask, exit_key, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->mlx_win, MotionNotify, PointerMotionMask, mouse_input, data);
	mlx_loop_hook(data->mlx, apply_moves, data);
}
