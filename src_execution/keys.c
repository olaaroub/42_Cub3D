/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:16:40 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/26 01:42:09 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    open_door(t_data *data)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (data->map.map[y])
    {
        x = 0;
        while (data->map.map[y][x])
        {
            if (data->map.map[y][x] == 'D')
                data->map.map[y][x] = 'O';
            x++;
        }
        y++;
    }
    data->door_open = 1;
}

void    close_door(t_data *data)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (data->map.map[y])
    {
        x = 0;
        while (data->map.map[y][x])
        {
            if (data->map.map[y][x] == 'O')
                data->map.map[y][x] = 'D';
            x++;
        }
        y++;
    }
    data->door_open = 0;
}

int key_press(int key, void *param)
{
    t_data  *data;
    data = (t_data *)param;
    if (key == XK_Escape)
        exit_key(data);
    else if(key == XK_f && !data->door_open)
        open_door(data);
    else if(key == XK_f && data->door_open)
        close_door(data);
    else  if (key == XK_d)
        data->d_pressed = 1;
    else if (key == XK_a)
        data->a_pressed = 1;
    else if (key == XK_w)
        data->w_pressed = 1;
    else if (key == XK_s)
        data->s_pressed = 1;
    else if (key == XK_Left)
        data->turn_left = 1;
    else if (key == XK_Right)
        data->turn_right = 1;

    return 0;
}

int key_release(int key, void *param)
{
    t_data *data;
    data = (t_data*)param;
    if (key == XK_d)
        data->d_pressed = 0;
    else if (key == XK_a)
        data->a_pressed = 0;
    else if (key == XK_w)
        data->w_pressed = 0;
    else if (key ==  XK_s)
        data->s_pressed = 0;
    else if (key == XK_Left )
        data->turn_left = 0;
    else if (key == XK_Right)
        data->turn_right = 0;

    return 0;
}
