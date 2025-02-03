/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:16:40 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/03 02:01:57 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void open_door2(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (data->map->map[y] && y < data->y_max)
    {
        x = 0;
        while (data->map->map[y][x] && x < data->x_max)
        {
                if (data->map->map[y][x] == 'D' && data->moves.opened == false)
                    data->map->map[y][x] = 'O';
            x++;
        }
        y++;
    }
    data->moves.opened = true;
}

void    close_door2(t_data *data)
{
    int x;
    int y;
    int player_x = (int)data->player.x / SOF;
    int player_y = (int)data->player.y / SOF;

    y = 0;
    if (data->map->map[player_y][player_x] == 'O')
        return ;
    while (data->map->map[y] && y < data->y_max)
    {
        x = 0;
        while (data->map->map[y][x] && x < data->x_max)
        {
                if ((data->map->map[y][x] == 'O') && data->moves.opened == true)
                    data->map->map[y][x] = 'D';
            x++;
        }
        y++;
    }
    data->moves.opened = false;
}
int	exit_key(void *param)
{
	t_data *data;

	data= (t_data *)param;
	mlx_destroy_image(data->mlx, data->img->img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}


int key_press(int key, void *param)
{
    t_data  *data;
    data = (t_data *)param;
    if (key == XK_Escape)
        exit_key(data);
    else if(key == XK_f && BONUS == 1)
       open_door2(data);
    else if(key == XK_e && BONUS == 1)
        close_door2(data);
    else  if (key == XK_d)
        data->moves.d_pressed = 1;
    else if (key == XK_a)
        data->moves.a_pressed = 1;
    else if (key == XK_w)
        data->moves.w_pressed = 1;
    else if (key == XK_s)
        data->moves.s_pressed = 1;
    else if (key == XK_Left)
        data->moves.turn_left = 1;
    else if (key == XK_Right)
        data->moves.turn_right = 1;
    return 0;
}

int key_release(int key, void *param)
{
    t_data *data;
    data = (t_data*)param;
    if (key == XK_d)
        data->moves.d_pressed = 0;
    else if (key == XK_a)
        data->moves.a_pressed = 0;
    else if (key == XK_w)
        data->moves.w_pressed = 0;
    else if (key ==  XK_s)
        data->moves.s_pressed = 0;
    else if (key == XK_Left )
        data->moves.turn_left = 0;
    else if (key == XK_Right)
        data->moves.turn_right = 0;
    return 0;
}
