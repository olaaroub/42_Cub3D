/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_pixels.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:57:19 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/06 03:40:58 by olaaroub         ###   ########.fr       */
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
		tex = DOOR_TEX[FRAMES];
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
		x = (int)(FIRE_TEX[FIRE_CURR_FRAME]->width * flag / 64)
			% FIRE_TEX[FIRE_CURR_FRAME]->width;
		offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
		if (offset < 0)
			offset = 0;
		index = offset * ((double)FIRE_TEX[FIRE_CURR_FRAME]->height
				/ data->wallhight);
		return (*(int *)(FIRE_TEX[FIRE_CURR_FRAME]->addr
			+ ((FIRE_TEX[FIRE_CURR_FRAME]->width * (index * 4) + (x * 4)))));
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
		tex = E_TEX;
	else
		tex = W_TEX;
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
	if (data->start_angle >= PI && data->start_angle < data->two_pi)
		tex = S_TEX;
	else
		tex = N_TEX;
	x = (int)(tex->width * data->hit.x / 64);
	x = x % tex->width;
	offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
	index = (double)offset * ((double)tex->height / data->wallhight);
	return (*(int *)(tex->addr + (tex->width * (index * 4) + (x * 4))));
}

// int	get_vertical_color(t_data *data, double y)
// {
// 	int	x;
// 	int	offset;
// 	int	index;
// 	int	color;

// 	color = get_door_pixel_color(data, y, data->hit.y);
// 	if (color != 69)
// 		return (color);
// 	color = get_fire_pixel_color(data, y, data->hit.y);
// 	if (color != 69)
// 		return (color);
// 	if ((data->start_angle >= (PI / 2)) && (data->start_angle < (3 * PI / 2)))
// 	{
// 		x = (int)(E_TEX->width * data->hit.y / 64)
// 			% E_TEX->width;
// 		offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
// 		index = offset * ((double)E_TEX->height / data->wallhight);
// 		return (*(int *)(E_TEX->addr + ((E_TEX->width * (index
// 							* 4) + (x * 4)))));
// 	}
// 	else
// 	{
// 		x = (int)(W_TEX->width * data->hit.y / 64)
// 			% W_TEX->width;
// 		offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
// 		index = (offset) * ((double)W_TEX->height / data->wallhight);
// 		return (*(int *)(W_TEX->addr + ((W_TEX->width * (index
// 							* 4) + (x * 4)))));
// 	}
// }

// int	get_horizontal_color(t_data *data, double y)
// {
// 	int	x;
// 	int	offset;
// 	int	index;
// 	int	color;

// 	color = get_door_pixel_color(data, y, data->hit.x);
// 	if (color != 69)
// 		return (color);
// 	color = get_fire_pixel_color(data, y, data->hit.x);
// 	if (color != 69)
// 		return (color);
// 	if (data->start_angle >= PI && data->start_angle < TOW_PI)
// 	{
// 		x = (int)(S_TEX->width * data->hit.x / 64)
// 			% S_TEX->width;
// 		offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
// 		index = offset * ((double)S_TEX->height / data->wallhight);
// 		return (*(int *)(S_TEX->addr + ((S_TEX->width
// 						* (index * 4) + (x * 4)))));
// 	}
// 	else
// 	{
// 		x = (int)(N_TEX->width * data->hit.x / 64)
// 			% N_TEX->width;
// 		offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
// 		index = offset * ((double)N_TEX->height / data->wallhight);
// 		return (*(int *)(N_TEX->addr + ((N_TEX->width
// 						* (index * 4) + (x * 4)))));
// 	}
// }

// static int	get_door_pixel_color(t_data *data, double y, double flag)
// {
// 	int	x;
// 	int	offset;
// 	int	index;

// 	if (data->hit_door && BONUS == 1)
// 	{
// 		x = (int)(DOOR_TEX[FRAMES]->width * flag / 64)
// 			% DOOR_TEX[FRAMES]->width;
// 		offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
// 		if (offset < 0)
// 			offset = 0;
// 		index = offset * ((double)DOOR_TEX[FRAMES]->height / data->wallhight);
// 		return (*(int *)(DOOR_TEX[FRAMES]->addr + ((DOOR_TEX[FRAMES]->width
// 						* (index * 4) + (x * 4)))));
// 	}
// 	if (data->hit_open_door && BONUS == 1)
// 	{
// 		x = (int)(DOOR_TEX[FRAMES]->width * flag / 64)
// 			% DOOR_TEX[FRAMES]->width;
// 		offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
// 		if (offset < 0)
// 			offset = 0;
// 		index = offset * ((double)DOOR_TEX[FRAMES]->height / data->wallhight);
// 		return (*(int *)(DOOR_TEX[FRAMES]->addr + ((DOOR_TEX[FRAMES]->width
// 						* (index * 4) + (x * 4)))));
// 	}
// 	else
// 		return (69);
// }