/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:14:08 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/20 16:18:49 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void isValidMove(t_data *data, int end_x, int end_y)
{
    int x;
    int y;
    char **map;

    x = data->x;
    y = data->y;
    map = data->map.map;

    if (data->map.map[y / SOF][(x + end_x + 2) / SOF] != '1'
        && data->map.map[y / SOF][(x + end_x  - 2) / SOF] != '1')
        data->x += end_x;
    if (data->map.map[(y + end_y + 2) / SOF][x / SOF] != '1'
        && data->map.map[(y + end_y - 2) / SOF][x / SOF] != '1')
        data->y += end_y;
}

void moveUp(t_data* data)
{
    int end_x;
    int end_y;

    end_x = roundf(FRM * cos(data->angle) * SPEED);
    end_y = roundf(FRM * sin(data->angle) * SPEED);
    isValidMove(data, end_x, end_y);
}

void moveDown(t_data* data)
{
    int end_x;
    int end_y;

    end_x = roundf(FRM * cos(data->angle + PI) * SPEED);
    end_y = roundf(FRM * sin(data->angle + PI) * SPEED);
    isValidMove(data, end_x, end_y);
}

void moveLeft(t_data* data)
{
    int end_x;
    int end_y;

    end_x = roundf(FRM * cos(data->angle - PI / 2) * SPEED);
    end_y = roundf(FRM * sin(data->angle - PI / 2) * SPEED);
    isValidMove(data, end_x, end_y);
}

void moveRight(t_data* data)
{
    int end_x;
    int end_y;

    end_x = roundf(FRM * cos(data->angle + PI / 2) * SPEED);
    end_y = roundf(FRM * sin(data->angle + PI / 2) * SPEED);
    isValidMove(data, end_x, end_y);
}

int move(void *parm)
{
    t_data *data = (t_data *)parm;

    if (data->fg_E)
        moveRight(data);
    if (data->fg_W)
        moveLeft(data);
    if (data->fg_N)
        moveUp(data);
    if (data->fg_S)
        moveDown(data);
    if (data->fg_left)
    {
        data->angle -= ROT_SPEED;
        if (data->angle < 0)
            data->angle += 2 * PI;
    }
    if (data->fg_right)
    {
        data->angle += ROT_SPEED;
        if (data->angle >= 2 * PI)
            data->angle -= 2 * PI;
    }
    render_3d(data);
    return 0;
}


