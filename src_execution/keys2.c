/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:14:08 by ohammou-          #+#    #+#             */
/*   Updated: 2024/12/26 20:19:29 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


int move(int key, void *parm)
{

    int x = data_global()->x;
    int y = data_global()->y;
    char **map = data_global()->map.map;
    t_img *img = parm;

    if(key == RIGHT && map[y / SOF][(x + SOP + FRM - 1) / SOF] != '1' && map[(y + SOP - 1) / SOF][(x + SOP + FRM - 1) / SOF] != '1')
    {
        data_global()->x += roundf(FRM * cos(data_global()->angle + (3 * PI) / 2));
        data_global()->y -= roundf(FRM * sin(data_global()->angle + (3 * PI) / 2));
    }
    if (key == LEFT && map[y / SOF][(x - FRM) / SOF] != '1' && map[(y + SOP - 1) / SOF][(x - FRM) / SOF] != '1')
    {
        data_global()->x += roundf(FRM * cos(data_global()->angle + PI / 2));
        data_global()->y -= roundf(FRM * sin(data_global()->angle + PI / 2));
    }
    if (key == DOWN && map[(y + SOP + FRM - 1) / SOF][x / SOF] != '1' && map[(y + SOP + FRM - 1) / SOF][(x + SOP - 1) / SOF] != '1')
    {
        data_global()->x += roundf(FRM * cos(data_global()->angle + PI));
        data_global()->y -= roundf(FRM * sin(data_global()->angle + PI));
    }
    if (key == UP && map[(y - FRM ) / SOF][x / SOF] != '1' && map[(y - FRM) / SOF][(x + SOP - 1) / SOF] != '1')
    {
        data_global()->x += roundf(FRM * cos(data_global()->angle));
        data_global()->y -= roundf(FRM * sin(data_global()->angle));
    }
    if (key == RIGHT_V)
    {
        data_global()->angle -= ROT_SPEED;
        if (data_global()->angle < 0)
            data_global()->angle += 2 * PI;
    }
    if (key == LEFT_V) 
    {
        data_global()->angle += ROT_SPEED;
        if (data_global()->angle >= 2 * PI)
            data_global()->angle -= 2 * PI;
    }
    printf("zawiya : %f   cos() = %f    sin()= %f   %d\n", data_global()->angle, cos(data_global()->angle), sin(data_global()->angle), data_global()->x);
    mlx_clear_window(data_global()->mlx, data_global()->mlx_win);
    usleep(200);
    drawing(img);
    return 0;
}

