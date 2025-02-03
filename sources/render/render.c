/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:32:59 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/03 18:23:41 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void render_hand(t_data *data)
{
    t_texture *tex = data->animations->hand_tex[HAND_CURR_FRAME];
    int        pos_x = (SCREEN_W - tex->width) / 2 ;
    int        pos_y = SCREEN_H - tex->height + data->animations->hand_y_offset;

    for (int y = 0; y < tex->height; y++)
    {
        for (int x = 0; x < tex->width; x++)
        {
            int color = *(int*)(tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel/8)));
            if ((color & 0x00FFFFFF) != 0)
                ft_pixelput(data->img, pos_x + x, pos_y + y, color);
        }
    }
}

static void draw_pixels(t_data *data, int x)
{
    int y;
    int color;

    y = 0;
    while (y < SCREEN_H)
    {
        while(y < data->start_draw)
            ft_pixelput(data->img, x, y++, data->map->ceiling_hex);
        while(y >= data->start_draw && y < data->end_draw)
        {
            if(data->is_vertical)
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

void render(t_data *data)
{
    int     x;
    double  angle_step;

    angle_step = FOV_ANGLE / SCREEN_W;
    data->start_angle = data->angle - (FOV_ANGLE / 2);
    if (data->start_angle < 0)
        data->start_angle += 2 * PI;
    x = -1;
    while (++x < SCREEN_W)
    {
        raycast(data);
        // data->ray_dist = raycast(data);
        // data->ray_dist *= cos(data->start_angle - data->angle);
        // data->projection_dist = (SCREEN_W / 2) / tan(FOV_ANGLE / 2);
        // data->wallhight = (SOF / data->ray_dist) * data->projection_dist;
        // data->start_draw = (SCREEN_H / 2) - (data->wallhight / 2);
        // data->end_draw = (SCREEN_H / 2) + (data->wallhight / 2);
        // if (data->start_draw < 0)
        //     data->start_draw = 0;
        // if (data->end_draw >= SCREEN_H)
        //     data->end_draw = SCREEN_H;
        draw_pixels(data, x);
        data->start_angle += angle_step;
    }
    if(BONUS == 1)
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
	mlx_loop_hook(data->mlx, handle_moves, data);
}


