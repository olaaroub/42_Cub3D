/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:14:08 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/30 02:42:52 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void is_valid_move(t_data *data, int end_x, int end_y)
{
    int x;
    int y;
    char **map;

    x = data->player_x;
    y = data->player_y;
    map = data->map.map;

    if ((data->map.map[y / SOF][(x + end_x + 2) / SOF] != '1'
        && data->map.map[y / SOF][(x + end_x  - 2) / SOF] != '1') && (data->map.map[y / SOF][(x + end_x + 2) / SOF] != 'D'))
        data->player_x += end_x;
    if ((data->map.map[(y + end_y + 2) / SOF][x / SOF] != '1'
        && data->map.map[(y + end_y - 2) / SOF][x / SOF] != '1') && (data->map.map[(y + end_y + 2) / SOF][x / SOF] != 'D'))
        data->player_y += end_y;
}

void move_up(t_data* data)
{
    int end_x;
    int end_y;

    end_x = roundf(FRM * cos(data->angle) * SPEED);
    end_y = roundf(FRM * sin(data->angle) * SPEED);
    is_valid_move(data, end_x, end_y);
}

void move_down(t_data* data)
{
    int end_x;
    int end_y;

    end_x = roundf(FRM * cos(data->angle + PI) * SPEED);
    end_y = roundf(FRM * sin(data->angle + PI) * SPEED);
    is_valid_move(data, end_x, end_y);
}

void move_left(t_data* data)
{
    int end_x;
    int end_y;

    end_x = roundf(FRM * cos(data->angle - PI / 2) * SPEED);
    end_y = roundf(FRM * sin(data->angle - PI / 2) * SPEED);
    is_valid_move(data, end_x, end_y);
}

void move_right(t_data* data)
{
    int end_x;
    int end_y;

    end_x = roundf(FRM * cos(data->angle + PI / 2) * SPEED);
    end_y = roundf(FRM * sin(data->angle + PI / 2) * SPEED);
    is_valid_move(data, end_x, end_y);
}



int move(void *parm)
{
    t_data *data = (t_data *)parm;
    static int i;

    if (data->d_pressed)
        move_right(data);
    if (data->a_pressed)
        move_left(data);
    if (data->w_pressed)
        move_up(data);
    if (data->s_pressed)
        move_down(data);
    if (data->turn_left)
    {
        data->angle -= ROT_SPEED;
        if (data->angle < 0)
            data->angle += 2 * PI;
    }

    if (data->turn_right)
    {
        data->angle += ROT_SPEED;
        if (data->angle >= 2 * PI)
            data->angle -= 2 * PI;
    }
    if(data->opened == true)
    {
        if(i % 4 == 0)
        {
            FRAMES++;
            if(FRAMES > 3)
                FRAMES = 3;
        }
        i++;
    }
    else if(data->opened == false)
    {
        if(i % 4 == 0)
        {
            FRAMES--;
            if(FRAMES < 0)
                FRAMES = 0;
        }
        i++;
    }
    if(i > 20)
        i = 0;
    render_3d(data);
    return 0;
}


