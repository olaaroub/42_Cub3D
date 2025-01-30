/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:12:01 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/30 21:36:53 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/*
    calculat the end positon of player

    claculat x:
        cos(O) = c / a (go to example 1 in learn.tldr file)
        x: c = a.cos(O);
    calculat y:
        sin(O) = b / a;
        y: b = a.sin(O);

    in the drawing_ray function the a is the len of ray;

*/

int drawing_ray(t_img *img, double angle, int ray_length, t_data *data)
{
    int x_start = data->player_x;
    int y_start = data->player_y;

    int x_end = x_start + ray_length * cos(angle);
    int y_end = y_start + ray_length * sin(angle);

    int dx = x_end - x_start;
    int dy = y_end - y_start;
    int steps = 0;
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    double x_inc = dx / (double)steps;
    double y_inc = dy / (double)steps;

    double x = x_start;
    double y = y_start;
    int i = 0;
    while (i <= steps)
    {
        ft_pixelput(img, round(x), round(y), 0x00FF00);
        x += x_inc;
        y += y_inc;
        i++;
    }
    return 0;
}

/*

    the prove to how I fined the first Intersection :
    ok, I have a  ray that  going in point P to A;

    y
    |___ A
    |  /|
    | / |
    |/__|________> x
     P

    - we have a equation is : cos(O) = Ax / |PA|  and sin(O) =  Ay /  |PA|;
    so: Ax  = |PA|.cos(O) and Ay = |PA|.sin(O);
    ok,  using this equation we try to  find  a equation that  find first point;
    we have a: Ax = x + ray.distance.cos(O) and Ay = y + ray.distance.sin(O);
    Ax: ray.distance = (Ax - x) /  cos(O);
    Ay:  Ay = Ay +  (Ax - x)  /  cos(O); // becose he has  a same ray len (same |PA| in above example);

    and if  we  want to calculat Ax we use the same method

*/
void vertical_intersection(t_data *data, t_vect *hit)
{
    t_vect ray_dir;
    double x, y;

    x = data->player_x;
    y = data->player_y;

    ray_dir.x = cos(data->start_angle);
    ray_dir.y = sin(data->start_angle);

    // if (fabs(ray_dir.x) < EPSILON)
    //     return;
    if (ray_dir.x < 0)
        hit->x = floor(x / SOF) * SOF - EPSILON;
    else
        hit->x = floor(x / SOF) * SOF + SOF;
    hit->y = y + ((hit->x - x) / ray_dir.x) * ray_dir.y;

}

double draw_vray(t_data *data , t_vect map, t_vect *v_hit, bool *hit_door, t_vect *door_coor_v, bool *hit_door_ov)
{
    t_vect hit;
    t_vect step;
    // (void)hit_door_ov;

    vertical_intersection(data, &hit);
    // if (fabs(cos(data->start_angle)) < EPSILON)
    //     return INT_MAX;
    if (cos(data->start_angle) > 0)
        step.x = SOF;
    else
        step.x = -SOF;
    step.y = step.x * tan(data->start_angle);
    while (hit.x >= 0 && hit.x < data->x_max * SOF &&
           hit.y >= 0 && hit.y < data->y_max * SOF)
    {
        map.x = (int)hit.x / SOF;
        map.y = (int)hit.y / SOF;
        if (map.y >= 0 && map.y < data->y_max &&
            map.x >= 0 && map.x < (int)ft_strlen(data->map.map[(int)map.y]))
        {
            if (data->map.map[(int)map.y][(int)map.x] == '1' || ((data->map.map[(int)map.y][(int)map.x] == 'D' ||
                data->map.map[(int)map.y][(int)map.x] == 'O') && BONUS == 1))
                {
                    if(data->map.map[(int)map.y][(int)map.x] == 'D')
                    {
                        door_coor_v->x = map.x;
                        door_coor_v->y = map.y;
                        *hit_door = true;
                    }
                    else if(data->map.map[(int)map.y][(int)map.x] == 'O')
                    {
                        door_coor_v->x = map.x;
                        door_coor_v->y = map.y;
                        *hit_door_ov = true;
                    }
                    break;
                }
        }
        else
            break;
        hit.x += step.x;
        hit.y += step.y;
    }
    v_hit->x = hit.x;
    v_hit->y = hit.y;
    return (sqrt(pow(hit.x - data->player_x, 2) + pow(hit.y - data->player_y, 2)));
}

void horizontal_intersection(t_data *data, t_vect *hit)
{
    double rayDirx;
    double rayDiry;
    double x;
    double y;

    x = data->player_x;
    y = data->player_y;
    rayDirx = cos(data->start_angle);
    rayDiry = sin(data->start_angle);

    // if (fabs(rayDiry) < EPSILON)
    //     return ;
    if (rayDiry < 0)
        hit->y = floor(y / SOF) * SOF - EPSILON;
    else
        hit->y = floor(y / SOF) * SOF + SOF;
    hit->x = x + ((hit->y - y) / rayDiry) * rayDirx;
}

double draw_hray(t_data *data, t_vect map, t_vect *h_hit, bool *hit_door, t_vect *door_coor_h, bool *hit_door_oh)
{
    t_vect hit;
    t_vect step;
    // (void)hit_door_oh;

    horizontal_intersection(data, &hit);
    // if (fabs(sin(data->start_angle)) < EPSILON)
    //     return INT_MAX;
    if (sin(data->start_angle) > 0)
        step.y = SOF;
    else
        step.y = -SOF;
    step.x = step.y / tan(data->start_angle);
    while (hit.x >= 0 && hit.x < data->x_max * SOF &&
           hit.y >= 0 && hit.y < data->y_max * SOF)
    {
        map.x = (int)(hit.x / SOF);
        map.y = (int)(hit.y / SOF);
        // printf("%c\n", data->map.map[(int)map.y][(int)map.x]);
        if (map.y >= 0 && map.y < data->y_max &&
            map.x >= 0 && map.x < (int)ft_strlen(data->map.map[(int)map.y]) &&
            (data->map.map[(int)map.y][(int)map.x] == '1' || ((data->map.map[(int)map.y][(int)map.x] == 'D' ||
             data->map.map[(int)map.y][(int)map.x] == 'O') && BONUS == 1)))
            {
                if(data->map.map[(int)map.y][(int)map.x] == 'D')
                {
                    door_coor_h->x = map.x;
                    door_coor_h->y = map.y;
                    *hit_door = true;
                }
                else if(data->map.map[(int)map.y][(int)map.x] == 'O')
                {
                    door_coor_h->x = map.x;
                    door_coor_h->y = map.y;
                    *hit_door_oh = true;
                }
                break;
            }
        hit.x += step.x;
        hit.y += step.y;
    }
    h_hit->x = hit.x;
    h_hit->y = hit.y;
    return (sqrt(pow(hit.x - data->player_x, 2) + pow(hit.y - data->player_y, 2)));
}

double get_ray_lenght(t_data *data)
{
    double hlen;
    double vlen;
    t_vect h_hit;
    t_vect v_hit;
    t_vect map;
    t_vect door_coor_h;
    t_vect door_coor_v;
    bool hit_door_h = false;
    bool hit_door_v = false;
    bool hit_door_oh = false;
    bool hit_door_ov = false;

    map.x = 0;
    map.y = 0;
    hlen = draw_hray(data, map, &h_hit, &hit_door_h, &door_coor_h, &hit_door_oh);
    vlen = draw_vray(data, map, &v_hit, &hit_door_v, &door_coor_v, &hit_door_ov);
    data->is_vertical = false;
    if (hlen < vlen)
    {
        data->hit_x = h_hit.x;
        data->hit_y = h_hit.y;
        data->door_coor.x = door_coor_h.x;
        data->door_coor.y = door_coor_h.y;
        data->hit_door = hit_door_h;
        data->hit_door_open = hit_door_oh;
        return hlen;
    }
    else
    {
        data->hit_x = v_hit.x;
        data->hit_y = v_hit.y;
        data->door_coor.x = door_coor_v.x;
        data->door_coor.y = door_coor_v.y;
        data->is_vertical = true;
        data->hit_door = hit_door_v;
        data->hit_door_open = hit_door_ov;
        return vlen;
    }
    return 0;
}

int get_vertical_color(t_data *data, double y)
{
  int x;
  int offset;
  int index;

    if(data->hit_door && BONUS == 1)
    {
        x = (int)(data->door_tex[FRAMES].width * data->hit_y / 64) % data->door_tex[FRAMES].width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        if(offset < 0)
            offset = 0;
        index = offset * ((double)data->door_tex[FRAMES].height / data->wallhight);
        return (*(int*)(data->door_tex[FRAMES].addr + ((data->door_tex[FRAMES].width * (index * 4) + (x * 4)))));
    }
    if(data->hit_door_open && BONUS == 1)
    {
        x = (int)(data->door_tex[FRAMES].width * data->hit_y / 64) % data->door_tex[FRAMES].width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        if(offset < 0)
            offset = 0;
        index = offset * ((double)data->door_tex[FRAMES].height / data->wallhight);
        return (*(int*)(data->door_tex[FRAMES].addr + ((data->door_tex[FRAMES].width * (index * 4) + (x * 4)))));
    }
    if((data->start_angle >= (PI / 2) )&& (data->start_angle < (3 * PI / 2)))
    {
        x = (int)(data->east_tex->width * data->hit_y / 64) % data->east_tex->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        index = offset * ((double)data->east_tex->height / data->wallhight);
        return(*(int*)(data->east_tex->addr + ((data->east_tex->width * (index * 4) + (x * 4)))));
    }
    else
    {
        x = (int)(data->west_tex->width * data->hit_y / 64) % data->west_tex->width;
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
        x = (int)(data->door_tex[FRAMES].width * data->hit_x / 64) % data->door_tex[FRAMES].width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        if(offset < 0)
            offset = 0;
        index = offset * ((double)data->door_tex[FRAMES].height / data->wallhight);
        return (*(int*)(data->door_tex[FRAMES].addr + ((data->door_tex[FRAMES].width * (index * 4) + (x * 4)))));
    }

    if(data->hit_door_open && BONUS == 1)
    {
        x = (int)(data->door_tex[FRAMES].width * data->hit_x / 64) % data->door_tex[FRAMES].width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        if(offset < 0)
            offset = 0;
        index = offset * ((double)data->door_tex[FRAMES].height / data->wallhight);
        return (*(int*)(data->door_tex[FRAMES].addr + ((data->door_tex[FRAMES].width * (index * 4) + (x * 4)))));
    }
    if (data->start_angle >= PI && data->start_angle < 2 * PI)
    {
        x = (int)(data->south_tex->width * data->hit_x / 64) % data->south_tex->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        if(offset < 0)
            offset = 0;
        index = offset * ((double)data->south_tex->height / data->wallhight);
        return (*(int*)(data->south_tex->addr + ((data->south_tex->width * (index * 4) + (x * 4)))));
    }
    else
    {
        x = (int)(data->north_tex->width * data->hit_x / 64) % data->north_tex->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        index = offset * ((double)data->north_tex->height / data->wallhight);
        return (*(int*)(data->north_tex->addr + ((data->north_tex->width * (index * 4) + (x * 4)))));
    }
}

void draw_3d(t_data *data, int x)
{
    int y;
    int color;

    y = 0;
    while (y < SCREEN_H)
    {
        while(y < data->start_draw)
            ft_pixelput(data->img, x, y++, data->map.ceiling_hex);
        while(y >= data->start_draw && y < data->end_draw)
        {
            if(data->is_vertical)
                color = get_vertical_color(data, y);
            else
                color = get_horizontal_color(data, y);
            ft_pixelput(data->img, x, y, color);
            y++;
        }
        ft_pixelput(data->img, x, y, data->map.floor_hex);
        y++;
    }
}

void render_3d(t_data *data)
{
    int     x;
    double  angle_step;

    angle_step = FOV_ANGLE / SCREEN_W;
    data->start_angle = data->angle - (FOV_ANGLE / 2);
    if (data->start_angle < 0)
        data->start_angle += 2 * PI;
    x = -1;
    while (++x < SCREEN_W)
    {
        data->ray_dis = get_ray_lenght(data);
        data->ray_dis *= cos(data->start_angle - data->angle);
        data->dis = (SCREEN_W / 2) / tan(FOV_ANGLE / 2);
        data->wallhight = (SOF / data->ray_dis) * data->dis;
        // printf("%f\n", data->ray_dis);
        data->start_draw = (SCREEN_H / 2) - (data->wallhight / 2);
        data->end_draw = (SCREEN_H / 2) + (data->wallhight / 2);
        if (data->start_draw < 0)
            data->start_draw = 0;
        if (data->end_draw >= SCREEN_H)
            data->end_draw = SCREEN_H;
        draw_3d(data, x);
        // drawing_ray(data->img, data->start_angle, data->ray_dis, data);
        data->start_angle += angle_step;
    }
    if(BONUS == 1)
        minimap(data);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}
