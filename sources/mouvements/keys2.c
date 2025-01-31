/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:14:08 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/31 16:44:57 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void is_valid_move(t_data *data, double end_x, double end_y)
{
    double next_x;
    double next_y;
    char **map;

    next_x = data->player_x + end_x;
    next_y = data->player_y + end_y;
    map = data->map.map;

    // printf("%c  %c  %c %c\n", map[(y + end_y - 2) / SOF][x / SOF], map[y / SOF][(x + end_x + 2) / SOF], map[(y + end_y + 2) / SOF][x / SOF] , map[(y + end_y - 2) / SOF][x / SOF]);
    if (map[(int)data->player_y / SOF][(int)(next_x + 2) / SOF] != '1'
        && map[(int)data->player_y / SOF][(int)(next_x - 2) / SOF] != '1'
        && map[(int)data->player_y / SOF][(int)(next_x + 2) / SOF] != 'D'
        && map[(int)data->player_y / SOF][(int)(next_x - 2) / SOF] != 'D')
        data->player_x = next_x;
    if (map[(int)(next_y + 2) / SOF][(int)data->player_x / SOF] != '1'
        && map[(int)(next_y  - 2) / SOF][(int)data->player_x / SOF] != '1'
        && map[(int)(next_y + 2) / SOF][(int)data->player_x / SOF] != 'D'
        && map[(int)(next_y  - 2) / SOF][(int)data->player_x / SOF] != 'D')
        data->player_y = next_y;
}

void move_up(t_data* data)
{
    double end_x;
    double end_y;

    end_x = FRM * cos(data->angle) * SPEED;
    end_y = FRM * sin(data->angle) * SPEED;
    is_valid_move(data, end_x, end_y);
}

void move_down(t_data* data)
{
    double end_x;
    double end_y;

    end_x = FRM * cos(data->angle + PI) * SPEED;
    end_y = FRM * sin(data->angle + PI) * SPEED;
    is_valid_move(data, end_x, end_y);
}

void move_left(t_data* data)
{
    double end_x;
    double end_y;

    end_x = FRM * cos(data->angle - PI / 2) * SPEED;
    end_y = FRM * sin(data->angle - PI / 2) * SPEED;
    is_valid_move(data, end_x, end_y);
}

void move_right(t_data* data)
{
    double end_x;
    double end_y;

    end_x = FRM * cos(data->angle + PI / 2) * SPEED;
    end_y = FRM * sin(data->angle + PI / 2) * SPEED;
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


