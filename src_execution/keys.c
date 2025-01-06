/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:16:40 by ohammou-          #+#    #+#             */
/*   Updated: 2024/12/26 20:29:05 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int key_press(int key, void *parm)
{
    if (key == ESC)
    {
        mlx_clear_window(data_global()->mlx, data_global()->mlx_win);
		exit(0);
    }
    if (key == RIGHT)
        data_global()->fg_E = 1;
    if (key == LEFT)
        data_global()->fg_W = 1;
    if (key == UP)
        data_global()->fg_N = 1;
    if (key == DOWN)
        data_global()->fg_S = 1;
    if (key == LEFT_V)
        data_global()->fg_left = 1;
    if (key == RIGHT_V)
        data_global()->fg_right = 1;
    move(parm);
    return 0;
}

int key_release(int key, void *parm)
{
    (void)parm;
    if (key == RIGHT)
        data_global()->fg_E = 0;
    if (key == LEFT)
        data_global()->fg_W = 0;
    if (key == UP)
        data_global()->fg_N = 0;
    if (key == DOWN)
        data_global()->fg_S = 0;
    if (key == LEFT_V)
        data_global()->fg_left = 0;
    if (key == RIGHT_V)
        data_global()->fg_right = 0;
    return 0;
}

int	krwa()
{
	exit(0);
	return (0);
}