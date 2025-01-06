/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:12:01 by ohammou-          #+#    #+#             */
/*   Updated: 2024/12/30 20:22:22 by ohammou-         ###   ########.fr       */
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

int drawing_ray(t_img *img, double angle, int ray_length)
{
    int x_start = data_global()->x;
    int y_start = data_global()->y;

    int x_end = x_start + ray_length * cos(angle);
    int y_end = y_start - ray_length * sin(angle);

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

void VerticalIntersection(double *Ay, double *Ax, double angle)
{
    double rayDirx;
    double rayDiry;
    double x, y;

    x = data_global()->x;
    y = data_global()->y;

    rayDirx = cos(angle);
    rayDiry = -sin(angle);

    if (fabs(rayDirx) < EPSILON)
        return;
    if (rayDirx < 0)
        *Ax = floor(x / SOF) * SOF - EPSILON;
    else
        *Ax = floor(x / SOF) * SOF + SOF;
    *Ay = y + ((*Ax - x) / rayDirx) * rayDiry;

}

double draw_rayWithVertical(double angle, int map_x, int map_y)
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
        if (map_x >= 0 && map_x < data_global()->x_max &&
            map_y >= 0 && map_y < data_global()->y_max)
        {
            if (data_global()->map.map[map_y][map_x] == '1')
                break;
        }
        else
            break;
        Ax += xstep;
        Ay -= ystep;
    }
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
    rayDiry = -sin(angle);

    if (fabs(rayDiry) < EPSILON)
        return ;
    if (rayDiry < 0)
        *Ay = floor(y / SOF) * SOF - EPSILON;
    else
        *Ay = floor(y / SOF) * SOF + SOF;

    *Ax = x + ((*Ay - y) / rayDiry) * rayDirx;
}

double draw_rayWithHorizontal(double angle, int map_x, int map_y)
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
        if (map_x >= 0 && map_x < data_global()->x_max &&
            map_y >= 0 && map_y < data_global()->y_max &&
            data_global()->map.map[map_y][map_x] == '1')
            break;

        Ax += xstep;
        Ay -= ystep;
    }
    return (sqrt(pow(Ax - data_global()->x, 2) + pow(Ay - data_global()->y, 2)));
}

double get_ray_lenght(double angle)
{
    double hlen;
    double vlen;
    int map_x;
    int map_y;

    hlen = draw_rayWithHorizontal(angle, map_x, map_y);
    vlen = draw_rayWithVertical(angle, map_x, map_y);
    if (hlen < vlen)
        return hlen;
    else
        return vlen;
    return 0;
}

void    render_3d(t_img *img)
{
    double    fov_angle = PI / 3; // 60-degree field of view
    int        num_rays = SCREEN_W; // One ray per screen column
    double    angle_step = fov_angle / num_rays;
    double    start_angle = data_global()->angle - (fov_angle / 2);
    double    ray_angle;

    for (int x = 0; x < SCREEN_W; x++)
    {
        // Calculate the current ray angle
        ray_angle = start_angle + x * angle_step;

        // Cast the ray to find the distance to the wall
        double    distance_to_wall = get_ray_lenght(ray_angle);

        // Correct for fish-eye distortion
        distance_to_wall *= cos(ray_angle - data_global()->angle);

        // Calculate the height of the wall slice
        double    projection_plane_dist = (SCREEN_W / 2) / tan(fov_angle / 2);
        int        wall_height = (int)((SOF / distance_to_wall) * projection_plane_dist);

        // Determine the starting and ending points for the wall slice
        int        wall_top = (SCREEN_H / 2) - (wall_height / 2);
        int        wall_bottom = (SCREEN_H / 2) + (wall_height / 2);

        // Clamp values to screen dimensions
        if (wall_top < 0)
            wall_top = 0;
        if (wall_bottom >= SCREEN_H)
            wall_bottom = SCREEN_H - 1;

        // Draw the wall slice
        for (int y = 0; y < SCREEN_H; y++)
        {
            if (y < wall_top)
                ft_pixelput(img, x, y, 0x0000FF); // Sky color
            else if (y > wall_bottom)
                ft_pixelput(img, x, y, 0x000000); // Floor color
            else
            {
                ft_pixelput(img, x, y, 0xFF0000); // Wall color
                if (y % 2 == 0)
                    ft_pixelput(img, x, y, 0x00FF00); // Wall color
            }
        }

    }
}

void drawing_rays(t_img *img)
{
    int screen_width = data_global()->x_max * SOF;
    double fov = PI / 3;
    double angle_step = fov / screen_width;
    double ray_angle;
    double start_angle = data_global()->angle - fov / 2;
    int i = 0;
    int ray;

    while (i < screen_width)
    {
        ray_angle = start_angle + i * angle_step;
        ray = get_ray_lenght(ray_angle);
        // rander3D(ray_angle, ray, img);
        drawing_ray(img, ray_angle, ray);
        i++;
    }
    put_img(img);
}
