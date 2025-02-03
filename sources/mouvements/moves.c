/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:19:25 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/03 02:04:03 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void is_valid_move(t_data *data, double end_x, double end_y)
{
    double next_x;
    double next_y;
    char **map;

    next_x = data->player.x + end_x;
    next_y = data->player.y + end_y;
    map = data->map->map;

    int grid_y = (int)data->player.y / SOF;
    int grid_x_plus = (int)(next_x + 2) / SOF;
    int grid_x_minus = (int)(next_x - 2) / SOF;

    if (!IS_BLOCKING_TILE(map[grid_y][grid_x_plus]) &&
        !IS_BLOCKING_TILE(map[grid_y][grid_x_minus]))
    {
        data->player.x = next_x;
    }

    // Y-axis movement check
    int grid_x = (int)data->player.x / SOF;
    int grid_y_plus = (int)(next_y + 2) / SOF;
    int grid_y_minus = (int)(next_y - 2) / SOF;

    if (!IS_BLOCKING_TILE(map[grid_y_plus][grid_x]) &&
        !IS_BLOCKING_TILE(map[grid_y_minus][grid_x]))
    {
        data->player.y = next_y;
    }

    // printf("%c  %c  %c %c\n", map[(y + end_y - 2) / SOF][x / SOF], map[y / SOF][(x + end_x + 2) / SOF], map[(y + end_y + 2) / SOF][x / SOF] , map[(y + end_y - 2) / SOF][x / SOF]);
    // if (map[(int)data->player.y / SOF][(int)(next_x + 2) / SOF] != '1'
    //     && map[(int)data->player.y / SOF][(int)(next_x - 2) / SOF] != '1'
    //     && map[(int)data->player.y / SOF][(int)(next_x + 2) / SOF] != 'D'
    //     && map[(int)data->player.y / SOF][(int)(next_x - 2) / SOF] != 'D')
    //     data->player.x = next_x;
    // if (map[(int)(next_y + 2) / SOF][(int)data->player.x / SOF] != '1'
    //     && map[(int)(next_y  - 2) / SOF][(int)data->player.x / SOF] != '1'
    //     && map[(int)(next_y + 2) / SOF][(int)data->player.x / SOF] != 'D'
    //     && map[(int)(next_y  - 2) / SOF][(int)data->player.x / SOF] != 'D')
    //     data->player.y = next_y;
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

int protect_value(int value, int min, int max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

static void update_door_animation(t_data *data) {
    static int door_counter;
    int frame_step;

    if(data->moves.opened == true)
        frame_step = 1;
    else
        frame_step = -1;
    if (door_counter % DOOR_FRAME_STEP == 0)
        FRAMES = protect_value(FRAMES + frame_step, 0, DOOR_FRAMES - 1);

    door_counter++;
    if(door_counter >= 100)
        door_counter = 0;
    if(door_counter <= 0)
        door_counter = 0;
}

int handle_moves(void *parm)
{
    t_data *data = (t_data *)parm;
    static unsigned int anim_counter;
    static unsigned int fire_counter;

    if (data->moves.d_pressed)
        move_right(data);
    if (data->moves.a_pressed)
        move_left(data);
    if (data->moves.w_pressed)
        move_up(data);
    if (data->moves.s_pressed)
        move_down(data);
    if (data->moves.turn_left)
    {
        data->angle -= ROT_SPEED;
        if (data->angle < 0)
            data->angle += TOW_PI;
    }
    if (data->moves.turn_right)
    {
        data->angle += ROT_SPEED;
        if (data->angle >= TOW_PI)
            data->angle -= TOW_PI;
    }
    update_door_animation(data);
    if (++anim_counter % ANIM_STEP == 0)
    {
        HAND_CURR_FRAME = (HAND_CURR_FRAME + 1) % HAND_FRAMES;
        data->animations->hand_y_offset = 5 * sin(ANIM_STEP * 0.01);
    }
    if(anim_counter >= UINT_MAX - 1000)
        anim_counter = 0;

    if (++fire_counter % FIRE_FRAME_STEP == 0)
        FIRE_CURR_FRAME = (FIRE_CURR_FRAME + 1) % FIRE_FRAMES;
    if(fire_counter >= UINT_MAX - 1000)
        fire_counter = 0;
    render(data);
    return 0;
}


