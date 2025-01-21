/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:16:40 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/20 16:08:39 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int key_press(int key, void *param)
{
    t_data  *data;
    data = (t_data *)param;
    if (key == ESC)
    {
        mlx_clear_window(data->mlx, data->mlx_win);
		exit(0);
    }
    else  if (key == RIGHT)
        data->fg_E = 1;
    else if (key == LEFT)
        data->fg_W = 1;
    else if (key == UP)
        data->fg_N = 1;
    else if (key == DOWN)
        data->fg_S = 1;
    else if (key == LEFT_V)
        data->fg_left = 1;
    else if (key == RIGHT_V)
        data->fg_right = 1;
    // move(parm);
    return 0;
}

int key_release(int key, void *param)
{
    t_data *data;
    data = (t_data*)param;
    if (key == RIGHT)
        data->fg_E = 0;
    else if (key == LEFT)
        data->fg_W = 0;
    else if (key == UP)
        data->fg_N = 0;
    else if (key == DOWN)
        data->fg_S = 0;
    else if (key == LEFT_V)
        data->fg_left = 0;
    else if (key == RIGHT_V)
        data->fg_right = 0;
    return 0;
}

int	krwa()
{
	exit(0);
	return (0);
}