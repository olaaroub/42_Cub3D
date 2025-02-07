/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_pixels.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:57:19 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/07 03:00:22 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_door_pixel_color(t_data *data, double y, double flag)
{
	int			x;
	int			offset;
	int			index;
	t_texture	*tex;

	if ((data->hit_door || data->hit_open_door) && BONUS == 1)
	{
		tex = data->anim->d_tex[data->anim->d_curr];
		x = (int)(tex->width * flag / 64);
		x %= tex->width;
		offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
		if (offset < 0)
			offset = 0;
		index = offset * ((double)tex->height / data->wallhight);
		return (*(int *)(tex->addr + (tex->width * (index * 4) + (x * 4))));
	}
	else
		return (69);
}

static int	get_fire_pixel_color(t_data *data, double y, double flag)
{
	int	x;
	int	offset;
	int	index;

	if (data->hit_fire && BONUS == 1)
	{
		x = (int)(data->anim->f_tex[data->anim->f_curr]->width * flag / 64)
			% data->anim->f_tex[data->anim->f_curr]->width;
		offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
		if (offset < 0)
			offset = 0;
		index = offset * ((double)data->anim->f_tex[data->anim->f_curr]->height
				/ data->wallhight);
		return (*(int *)(data->anim->f_tex[data->anim->f_curr]->addr
			+ ((data->anim->f_tex[data->anim->f_curr]->width
					* (index * 4) + (x * 4)))));
	}
	else
		return (69);
}

int	get_vertical_color(t_data *data, double y)
{
	int			color;
	t_texture	*tex;
	int			x;
	int			offset;
	int			index;

	color = get_door_pixel_color(data, y, data->hit.y);
	if (color != 69)
		return (color);
	color = get_fire_pixel_color(data, y, data->hit.y);
	if (color != 69)
		return (color);
	if ((data->start_angle >= (PI / 2)) && (data->start_angle < (3 * PI / 2)))
		tex = data->w_tex;
	else
		tex = data->e_tex;
	x = (int)(tex->width * data->hit.y / 64);
	x = x % tex->width;
	offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
	index = offset * ((double)tex->height / data->wallhight);
	return (*(int *)(tex->addr + (tex->width * (index * 4) + (x * 4))));
}

int	get_horizontal_color(t_data *data, double y)
{
	int			color;
	t_texture	*tex;
	int			x;
	int			offset;
	int			index;

	color = get_door_pixel_color(data, y, data->hit.x);
	if (color != 69)
		return (color);
	color = get_fire_pixel_color(data, y, data->hit.x);
	if (color != 69)
		return (color);
	if (data->start_angle >= PI && data->start_angle < TWO_PI)
		tex = data->n_tex;
	else
		tex = data->s_tex;
	x = (int)(tex->width * data->hit.x / 64);
	x = x % tex->width;
	offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
	index = (double)offset * ((double)tex->height / data->wallhight);
	return (*(int *)(tex->addr + (tex->width * (index * 4) + (x * 4))));
}
