/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:14:08 by ohammou-          #+#    #+#             */
/*   Updated: 2024/12/27 16:47:02 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool isValidMove(int end_x, int end_y)
{
    int x;
    int y;
    char **map;

    x = data_global()->x;
    y = data_global()->y;
    map = data_global()->map.map;
    if (map[(y - end_y) / SOF][(x + end_x) / SOF] != '1'
            && map[(y - end_y) / SOF][(x + SOP - 1 + end_x) / SOF] != '1'
            && map[(y - end_y + SOP - 1) / SOF][(x + end_x) / SOF] != '1'
            && map[(y - end_y + SOP - 1) / SOF][(x + end_x + SOP - 1) / SOF] != '1')
        return true;
    
    return false;
}

void moveUp()
{
    int end_x;
    int end_y;

    end_x = roundf(FRM * cos(data_global()->angle) * SPEED);
    end_y = roundf(FRM * sin(data_global()->angle) * SPEED);
    if (isValidMove(end_x, end_y))
    {
        data_global()->x += end_x;
        data_global()->y -= end_y;
    }
}

void moveDown()
{
    int end_x;
    int end_y;

    end_x = roundf(FRM * cos(data_global()->angle + PI) * SPEED);
    end_y = roundf(FRM * sin(data_global()->angle + PI) * SPEED);

    if (isValidMove(end_x, end_y))
    {
        data_global()->x += end_x;
        data_global()->y -= end_y;
    }
}

void moveLeft()
{
    int end_x;
    int end_y;

    end_x = roundf(FRM * cos(data_global()->angle + PI / 2) * SPEED);
    end_y = roundf(FRM * sin(data_global()->angle + PI / 2) * SPEED);
    if (isValidMove(end_x, end_y))
    {
        data_global()->x += end_x;
        data_global()->y -= end_y;
    }
}

void moveRight()
{
    int end_x;
    int end_y;

    end_x = roundf(FRM * cos(data_global()->angle + (3 * PI) / 2) * SPEED);
    end_y = roundf(FRM * sin(data_global()->angle + (3 * PI) / 2) * SPEED);
    if(isValidMove(end_x, end_y))
    {
        data_global()->x += end_x;
        data_global()->y -= end_y;
    }   
}

int move(int key, void *parm)
{
    t_img *img = parm;

    if (key == RIGHT)
        moveRight();
    if (key == LEFT)
        moveLeft();
    if (key == UP)
        moveUp();
    if (key == DOWN)
        moveDown();
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
    mlx_clear_window(data_global()->mlx, data_global()->mlx_win);
    drawing(img);
    return 0;
}

