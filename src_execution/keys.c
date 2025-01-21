/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:16:40 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/21 18:13:11 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int key_press(int key, void *param)
{
    t_data  *data;
    data = (t_data *)param;
    if (key == ESC)
        exit_key(data);
    else  if (key == RIGHT)
        data->d_pressed = 1;
    else if (key == LEFT)
        data->a_pressed = 1;
    else if (key == UP)
        data->w_pressed = 1;
    else if (key == DOWN)
        data->s_pressed = 1;
    else if (key == LEFT_V)
        data->turn_left = 1;
    else if (key == RIGHT_V)
        data->turn_right = 1;
    return 0;
}

int key_release(int key, void *param)
{
    t_data *data;
    data = (t_data*)param;
    if (key == RIGHT)
        data->d_pressed = 0;
    else if (key == LEFT)
        data->a_pressed = 0;
    else if (key == UP)
        data->w_pressed = 0;
    else if (key == DOWN)
        data->s_pressed = 0;
    else if (key == LEFT_V)
        data->turn_left = 0;
    else if (key == RIGHT_V)
        data->turn_right = 0;
    return 0;
}
