/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:12:01 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/22 02:29:32 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


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

// int drawing_ray(t_img *img, double angle, int ray_length)
// {
//     int x_start = data_global()->x;
//     int y_start = data_global()->y;

//     int x_end = x_start + ray_length * cos(angle);
//     int y_end = y_start + ray_length * sin(angle);

//     int dx = x_end - x_start;
//     int dy = y_end - y_start;
//     int steps = 0;
//     if (abs(dx) > abs(dy))
//         steps = abs(dx);
//     else
//         steps = abs(dy);
//     double x_inc = dx / (double)steps;
//     double y_inc = dy / (double)steps;

//     double x = x_start;
//     double y = y_start;
//     int i = 0;
//     while (i <= steps)
//     {
//         ft_pixelput(img, round(x), round(y), 0x00FF00);
//         x += x_inc;
//         y += y_inc;
//         i++;
//     }
//     return 0;
// }

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
void VerticalIntersection(t_data *data, double *Ay, double *Ax)
{
    double rayDirx;
    double rayDiry;
    double x, y;

    x = data->player_x;
    y = data->player_y;

    rayDirx = cos(data->start_angle);
    rayDiry = sin(data->start_angle);

    if (fabs(rayDirx) < EPSILON)
        return;
    if (rayDirx < 0)
        *Ax = floor(x / SOF) * SOF - EPSILON;
    else
        *Ax = floor(x / SOF) * SOF + SOF;
    *Ay = y + ((*Ax - x) / rayDirx) * rayDiry;

}

double draw_rayWithVertical(t_data *data , int map_x, int map_y, t_data *vdata)
{
    double Ay;
    double Ax;
    double xstep;
    double ystep;

    VerticalIntersection(data, &Ay, &Ax);
    if (fabs(cos(data->start_angle)) < EPSILON)
        return INT_MAX;
    if (cos(data->start_angle) > 0)
        xstep = SOF;
    else
        xstep = -SOF;
    ystep = xstep * tan(data->start_angle);
    while (Ax >= 0 && Ax < data->x_max * SOF &&
           Ay >= 0 && Ay < data->y_max * SOF)
    {
        map_x = (int)Ax / SOF;
        map_y = (int)Ay / SOF;
        if (map_y >= 0 && map_y < data->y_max &&
            map_x >= 0 && map_x < (int)ft_strlen(data->map.map[map_y]))
        {
            if (data->map.map[map_y][map_x] == '1')
                break;
        }
        else
            break;
        Ax += xstep;
        Ay += ystep;
    }
    vdata->hit_x = Ax;
    vdata->hit_y = Ay;
    return (sqrt(pow(Ax - data->player_x, 2) + pow(Ay - data->player_y, 2)));
}

void HorizontalIntersection(t_data *data, double *Ay, double *Ax)
{
    double rayDirx;
    double rayDiry;
    double x;
    double y;

    x = data->player_x;
    y = data->player_y;
    rayDirx = cos(data->start_angle);
    rayDiry = sin(data->start_angle);

    if (fabs(rayDiry) < EPSILON)
        return ;
    if (rayDiry < 0)
        *Ay = floor(y / SOF) * SOF - EPSILON;
    else
        *Ay = floor(y / SOF) * SOF + SOF;

    *Ax = x + ((*Ay - y) / rayDiry) * rayDirx;
}

double draw_rayWithHorizontal(t_data *data, int map_x, int map_y, t_data *hdata)
{
    double Ay;
    double Ax;
    double xstep;
    double ystep;

    HorizontalIntersection(data, &Ay, &Ax);
    if (fabs(sin(data->start_angle)) < EPSILON)
        return INT_MAX;
    if (sin(data->start_angle) > 0)
        ystep = SOF;
    else
        ystep = -SOF;
    xstep = ystep / tan(data->start_angle);
    while (Ax >= 0 && Ax < data->x_max * SOF &&
           Ay >= 0 && Ay < data->y_max * SOF)
    {
        map_x = (int)(Ax / SOF);
        map_y = (int)(Ay / SOF);
        if (map_y >= 0 && map_y < data->y_max &&
            map_x >= 0 && map_x < (int)ft_strlen(data->map.map[map_y]) &&
            data->map.map[map_y][map_x] == '1')
            break;
        Ax += xstep;
        Ay += ystep;
    }
    hdata->hit_x = Ax;
    hdata->hit_y = Ay;
    return (sqrt(pow(Ax - data->player_x, 2) + pow(Ay - data->player_y, 2)));
}

double get_ray_lenght(t_data *data)
{
    double hlen;
    double vlen;
    t_data vdata;
    t_data hdata;

    vdata.map_x = 0;
    vdata.map_y = 0;
    hlen = draw_rayWithHorizontal(data, vdata.map_x, vdata.map_y, &hdata);
    vlen = draw_rayWithVertical(data, vdata.map_x, vdata.map_y, &vdata);
    data->is_vertical = false;
    if (hlen < vlen)
    {
        data->hit_x = hdata.hit_x;
        data->hit_y = hdata.hit_y;
        return hlen;
    }
    else
    {
        data->hit_x = vdata.hit_x;
        data->hit_y = vdata.hit_y;
        data->is_vertical = true;
        return vlen;
    }
    return 0;
}

int get_vertical_color(t_data *data, double y)
{
  int x;
  int offset;
  int index;
//   printf("data->ray_angle = %f\n", data->start_angle);
    if((data->start_angle >= (PI / 2) )&& (data->start_angle < (3 * PI / 2)))
    {
        x = (int)(data->east_tex->width * data->hit_y / 64) % data->east_tex->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        index = offset * ((double)data->east_tex->height / data->wallhight);
        return(*(int*)(data->east_tex->addr + ((data->east_tex->width * (index * 4) + (x * 4)))));
    }
    else {
        x = (int)(data->west_tex->width * data->hit_y / 64) % data->west_tex->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        index = offset * ((double)data->west_tex->height / data->wallhight);
        return (*(int*)(data->west_tex->addr + ((data->west_tex->width * (index * 4) + (x * 4)))));
    }
}

int get_horizontal_color(t_data *data, double y)
{
    int x;
    int offset;
    int index;
    // printf("data->start_angle = %f\n", data->start_angle);
    if (data->start_angle >= PI && data->start_angle < 2 * PI)
    {
        x = (int)(data->south_tex->width * data->hit_x / 64) % data->south_tex->width;
        offset = y + (data->wallhight / 2) - (SCREEN_H / 2);
        index = offset * ((double)data->south_tex->height / data->wallhight);
        return (*(int*)(data->south_tex->addr + ((data->south_tex->width * (index * 4) + (x * 4)))));
    }
    else{
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
        {
            ft_pixelput(data->img, x, y, data->map.ceiling_hex);
            y++;
        }
        // int texture_offset_x ;
        // if (data->is_vertical)
        //     texture_offset_x = (int)data->hit_y % SOF;
        // else
        //     texture_offset_x = (int)data->hit_x % SOF;
        while(y >= data->start_draw && y < data->end_draw)
        {
            if(data->is_vertical)
                color = get_vertical_color(data, y);
            else
                color = get_horizontal_color(data, y);
            // int distance_from_top = y - (SCREEN_H / 2) + (data->wallhight / 2);
            // int texture_offset_y = distance_from_top * (float)(64.0 / data->wallhight);
            // color = ((int *)data->north_tex->addr)[64 * texture_offset_y + texture_offset_x];
            ft_pixelput(data->img, x, y, color);
            y++;
        }
        ft_pixelput(data->img, x, y, data->map.floor_hex);
        y++;
    }
    // 0x4C585B   0x7E99A3
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
        data->start_draw = (SCREEN_H / 2) - (data->wallhight / 2);
        data->end_draw = (SCREEN_H / 2) + (data->wallhight / 2);
        if (data->start_draw < 0)
            data->start_draw = 0;
        if (data->end_draw >= SCREEN_H)
            data->end_draw = SCREEN_H - 1;
        draw_3d(data, x);
        data->start_angle += angle_step;
    }
    // minimap(data->img);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}

// void drawing_rays(t_img *img)
// {
//     int screen_width = data_global()->x_max * SOF;
//     double fov = PI / 3;
//     double angle_step = fov / screen_width;
//     double ray_angle;
//     double start_angle = data_global()->angle - fov / 2;
//     int i = 0;
//     int ray;

//     while (i < screen_width)
//     {
//         ray_angle = start_angle + i * angle_step;
//         ray = get_ray_lenght(ray_angle);
//         drawing_ray(img, ray_angle, ray);
//         i++;
//     }
//     put_img(img);
// }
