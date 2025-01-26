/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:16:40 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/26 21:08:40 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void open_door2(t_data *data)
{
    int x;
    int y;
    // int player_x = (int)data->player_x / SOF;
    // int player_y = (int)data->player_y / SOF;

    // y = player_y - 3;
    y = 0;
    while (y < data->y_max)
    {
        // x = player_x - 3;
        x = 0;
        while (x < data->x_max)
        {
            // if (y < data->y_max &&  x < data->x_max)
                if (data->map.map[y][x] == 'D')
                    if((x == data->door_coor.x && y == data->door_coor.y))
                            data->map.map[y][x] = 'O';
            x++;
        }
        y++;
    }
}

void close_door2(t_data *data)
{
    int x;
    int y;
    int player_x = (int)data->player_x / SOF;
    int player_y = (int)data->player_y / SOF;

    // y = player_y - 3;
    y = 0;
    while (y < data->y_max)
    {
        // x = player_x - 3;
        x = 0;
        while (x < data->x_max)
        {
            // if ( y < data->y_max && x < data->x_max)
                if (data->map.map[y][x] == 'O' && (y != player_y || x != player_x))
                    if((x == data->door_coor.x && y == data->door_coor.y))
                            data->map.map[y][x] = 'D';
            x++;
        }
        y++;
    }
}

int key_press(int key, void *param)
{
    t_data  *data;
    data = (t_data *)param;
    if (key == XK_Escape)
        exit_key(data);
    else if(key == XK_f)
        open_door2(data);
    else if(key == XK_e)
        close_door2(data);
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
