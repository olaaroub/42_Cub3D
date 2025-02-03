/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_pixels.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:57:19 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/03 01:58:09 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_vertical_color(t_data *data, double y)
{
  int x;
  int offset;
  int index;

    if(data->hit_door && BONUS == 1)
    {
        x = (int)(DOOR_TEX[FRAMES]->width * data->hit.y / 64) % DOOR_TEX[FRAMES]->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        if(offset < 0)
            offset = 0;
        index = offset * ((double)DOOR_TEX[FRAMES]->height / data->wallhight);
        return (*(int*)(DOOR_TEX[FRAMES]->addr + ((DOOR_TEX[FRAMES]->width * (index * 4) + (x * 4)))));
    }

    if(data->hit_fire && BONUS == 1)
    {
        x = (int)(FIRE_TEX[FIRE_CURR_FRAME]->width * data->hit.y / 64) % FIRE_TEX[FIRE_CURR_FRAME]->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        if(offset < 0)
            offset = 0;
        index = offset * ((double)FIRE_TEX[FIRE_CURR_FRAME]->height / data->wallhight);
        return (*(int*)(FIRE_TEX[FIRE_CURR_FRAME]->addr + ((FIRE_TEX[FIRE_CURR_FRAME]->width * (index * 4) + (x * 4)))));
    }

    if(data->hit_open_door && BONUS == 1)
    {
        x = (int)(DOOR_TEX[FRAMES]->width * data->hit.y / 64) % DOOR_TEX[FRAMES]->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        if(offset < 0)
            offset = 0;
        index = offset * ((double)DOOR_TEX[FRAMES]->height / data->wallhight);
        return (*(int*)(DOOR_TEX[FRAMES]->addr + ((DOOR_TEX[FRAMES]->width * (index * 4) + (x * 4)))));
    }
    if((data->start_angle >= (PI / 2) )&& (data->start_angle < (3 * PI / 2)))
    {
        x = (int)(data->east_tex->width * data->hit.y / 64) % data->east_tex->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        index = offset * ((double)data->east_tex->height / data->wallhight);
        return(*(int*)(data->east_tex->addr + ((data->east_tex->width * (index * 4) + (x * 4)))));
    }
    else
    {
        x = (int)(data->west_tex->width * data->hit.y / 64) % data->west_tex->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        index = (offset) * ((double)data->west_tex->height / data->wallhight);
        return (*(int*)(data->west_tex->addr + ((data->west_tex->width * (index * 4) + (x * 4)))));
    }
}


int get_horizontal_color(t_data *data, double y)
{
    int x;
    int offset;
    int index;
    if(data->hit_door && BONUS == 1)
    {
        x = (int)(DOOR_TEX[FRAMES]->width * data->hit.x / 64) % DOOR_TEX[FRAMES]->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        if(offset < 0)
            offset = 0;
        index = offset * ((double)DOOR_TEX[FRAMES]->height / data->wallhight);
        return (*(int*)(DOOR_TEX[FRAMES]->addr + ((DOOR_TEX[FRAMES]->width * (index * 4) + (x * 4)))));
    }

    if(data->hit_fire && BONUS == 1)
    {
        x = (int)(FIRE_TEX[FIRE_CURR_FRAME]->width * data->hit.x / 64) % FIRE_TEX[FIRE_CURR_FRAME]->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        if(offset < 0)
            offset = 0;
        index = offset * ((double)FIRE_TEX[FIRE_CURR_FRAME]->height / data->wallhight);
        return (*(int*)(FIRE_TEX[FIRE_CURR_FRAME]->addr + ((FIRE_TEX[FIRE_CURR_FRAME]->width * (index * 4) + (x * 4)))));
    }

    if(data->hit_open_door && BONUS == 1)
    {
        x = (int)(DOOR_TEX[FRAMES]->width * data->hit.x / 64) % DOOR_TEX[FRAMES]->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        if(offset < 0)
            offset = 0;
        index = offset * ((double)DOOR_TEX[FRAMES]->height / data->wallhight);
        return (*(int*)(DOOR_TEX[FRAMES]->addr + ((DOOR_TEX[FRAMES]->width * (index * 4) + (x * 4)))));
    }
    if (data->start_angle >= PI && data->start_angle < 2 * PI)
    {
        x = (int)(data->south_tex->width * data->hit.x / 64) % data->south_tex->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        if(offset < 0)
            offset = 0;
        index = offset * ((double)data->south_tex->height / data->wallhight);
        return (*(int*)(data->south_tex->addr + ((data->south_tex->width * (index * 4) + (x * 4)))));
    }
    else
    {
        x = (int)(data->north_tex->width * data->hit.x / 64) % data->north_tex->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        index = offset * ((double)data->north_tex->height / data->wallhight);
        return (*(int*)(data->north_tex->addr + ((data->north_tex->width * (index * 4) + (x * 4)))));
    }
}

