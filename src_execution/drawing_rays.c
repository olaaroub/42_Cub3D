/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:12:01 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/19 16:03:19 by ohammou-         ###   ########.fr       */
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
void VerticalIntersection(double *Ay, double *Ax, double angle)
{
    double rayDirx;
    double rayDiry;
    double x, y;

    x = data_global()->x;
    y = data_global()->y;

    rayDirx = cos(angle);
    rayDiry = sin(angle);

    if (fabs(rayDirx) < EPSILON)
        return;
    if (rayDirx < 0)
        *Ax = floor(x / SOF) * SOF - EPSILON;
    else
        *Ax = floor(x / SOF) * SOF + SOF;
    *Ay = y + ((*Ax - x) / rayDirx) * rayDiry;

}

double draw_rayWithVertical(double angle, int map_x, int map_y, t_data *vdata)
{
    double Ay;
    double Ax;
    double xstep;
    double ystep;

    VerticalIntersection(&Ay, &Ax, angle);
    if (fabs(cos(angle)) < EPSILON)
        return INT_MAX;
    if (cos(angle) > 0)
        xstep = SOF;
    else
        xstep = -SOF;
    ystep = xstep * tan(angle);
    while (Ax >= 0 && Ax < data_global()->x_max * SOF &&
           Ay >= 0 && Ay < data_global()->y_max * SOF)
    {
        map_x = (int)Ax / SOF;
        map_y = (int)Ay / SOF;
        if (map_y >= 0 && map_y < data_global()->y_max &&
            map_x >= 0 && map_x < (int)ft_strlen(data_global()->map.map[map_y]))
        {
            if (data_global()->map.map[map_y][map_x] == '1')
                break;
        }
        else
            break;
        Ax += xstep;
        Ay += ystep;
    }
    vdata->hit_x = Ax;
    vdata->hit_y = Ay;
    return (sqrt(pow(Ax - data_global()->x, 2) + pow(Ay - data_global()->y, 2)));
}

void HorizontalIntersection(double *Ay, double *Ax, double angle)
{
    double rayDirx;
    double rayDiry;
    double x;
    double y;

    x = data_global()->x;
    y = data_global()->y;
    rayDirx = cos(angle);
    rayDiry = sin(angle);

    if (fabs(rayDiry) < EPSILON)
        return ;
    if (rayDiry < 0)
        *Ay = floor(y / SOF) * SOF - EPSILON;
    else
        *Ay = floor(y / SOF) * SOF + SOF;

    *Ax = x + ((*Ay - y) / rayDiry) * rayDirx;
}

double draw_rayWithHorizontal(double angle, int map_x, int map_y, t_data *hdata)
{
    double Ay;
    double Ax;
    double xstep;
    double ystep;

    HorizontalIntersection(&Ay, &Ax, angle);
    if (fabs(sin(angle)) < EPSILON)
        return INT_MAX;
    if (sin(angle) > 0)
        ystep = SOF;
    else
        ystep = -SOF;
    xstep = ystep / tan(angle);
    while (Ax >= 0 && Ax < data_global()->x_max * SOF &&
           Ay >= 0 && Ay < data_global()->y_max * SOF)
    {
        map_x = (int)(Ax / SOF);
        map_y = (int)(Ay / SOF);
        if (map_y >= 0 && map_y < data_global()->y_max &&
            map_x >= 0 && map_x < (int)ft_strlen(data_global()->map.map[map_y]) &&
            data_global()->map.map[map_y][map_x] == '1')
            break;
        Ax += xstep;
        Ay += ystep;
    }
    hdata->hit_x = Ax;
    hdata->hit_y = Ay;
    return (sqrt(pow(Ax - data_global()->x, 2) + pow(Ay - data_global()->y, 2)));
}

double get_ray_lenght(double angle)
{
    double hlen;
    double vlen;
    t_data vdata;
    t_data hdata;

    vdata.map_x = 0;
    vdata.map_y = 0;
    hlen = draw_rayWithHorizontal(angle, vdata.map_x, vdata.map_y, &hdata);
    vlen = draw_rayWithVertical(angle, vdata.map_x, vdata.map_y, &vdata);
    data_global()->is_vertical = false;
    if (hlen < vlen)
    {
        data_global()->hit_x = hdata.hit_x;
        data_global()->hit_y = hdata.hit_y;
        return hlen;
    }
    else
    {
        data_global()->hit_x = vdata.hit_x;
        data_global()->hit_y = vdata.hit_y;
        data_global()->is_vertical = true;
        return vlen;
    }
    return 0;
}

void draw_3d(t_img *img ,t_data data, int x)
{
    int y;
    int color;

    y = 0;
    while (y < SCREEN_H)
    {
        if (y < data.start_draw)
              ft_pixelput(img, x, y, data_global()->map.ceiling_hex);
        else if (y >= data.start_draw && y <= data.end_draw)
        {
            if (data_global()->is_vertical)
                color = rgb_to_hex(76,88,91);
            else
                color = rgb_to_hex(126, 153, 163);
            ft_pixelput(img, x, y, color);
        }
        else
            ft_pixelput(img, x, y, data_global()->map.floor_hex);
        y++;
    }
    // 0x4C585B   0x7E99A3
}

void render_3d(t_img *img)
{
    t_data data;
    int x;

    data.angle_step = FOV_ANGLE / SCREEN_W;
    data.start_angle = data_global()->angle - FOV_ANGLE / 2;
    x = 0;
    while (x < SCREEN_W)
    {
        data.ray_dis = get_ray_lenght(data.start_angle);
        data.ray_dis *= cos(data.start_angle - data_global()->angle);
        data.dis = (SCREEN_W / 2) / tan(FOV_ANGLE / 2);
        data.wallhight = (SOF / data.ray_dis) * data.dis;
        data.start_draw = (SCREEN_H / 2) - (data.wallhight / 2);
        data.end_draw = (SCREEN_H / 2) + (data.wallhight / 2);
        if (data.start_draw < 0)
            data.start_draw = 0;
        if (data.end_draw >= SCREEN_H)
            data.end_draw = SCREEN_H - 1;
        draw_3d(img, data, x);
        data.start_angle += data.angle_step;
        x++;
    }
    minimap(img);
    put_img(img);
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
