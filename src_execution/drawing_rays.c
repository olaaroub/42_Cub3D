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

int get_length(double ray_angle)
{
    int x_start = data_global()->x + SOP / 2;
    int y_start = data_global()->y + SOP / 2;

    char **map = data_global()->map.map;

    int screen_width = data_global()->x_max * 60;  // Assuming this is defined
    int screen_height = data_global()->y_max * 60; // Assuming this is defined

    double x = x_start;
    double y = y_start;

    double step_size = 1.0; // Step size to move along the ray
    int max_length = 1000; // Maximum ray length (arbitrary large value)
    int steps = 0;

    while (steps < max_length) 
    {
        // Increment along the ray
        x += step_size * cos(ray_angle);
        y -= step_size * sin(ray_angle);

        // Convert to grid coordinates
        int grid_x = (int)(x / SOF);
        int grid_y = (int)(y / SOF);

        // Check if we're outside the screen boundaries
        if (x < 0 || y < 0 || x >= screen_width || y >= screen_height)
            break;

        // Check if the ray hit a wall
        if (map[grid_y][grid_x] == '1')
            break;

        steps++;
    }

    return steps * step_size; // Return the length of the ray
}


int drawing_ray(t_img *img, double angle, int ray_length)
{
    int x_start = data_global()->x + SOP / 2;
    int y_start = data_global()->y + SOP / 2;

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
        ft_pixelput(img, (int)x, (int)y, 0x00FF00);
        x += x_inc;
        y += y_inc;
        i++;
    }
    return 0;
}

void drawing_rays(t_img *img)
{
    int screen_width = data_global()->x_max * 60;
    double fov = PI / 3;
    double angle_step = fov / screen_width;
    double ray_angle;
    double start_angle = data_global()->angle - fov / 2;
    int i = 0;
    int ray;

    while (i < screen_width)
    {
        ray_angle = start_angle + i * angle_step;
        ray = get_length(ray_angle);
        drawing_ray(img, ray_angle, ray);
        i++;
    }
    // put_img(img);
}

// void drawing_rays(t_img *img)
// {
//     double start = data_global()->angle - PI / 6;
//     double end = data_global()->angle + PI  / 6;

//     while (start < end)
//     {
//         drawing_ray(img, start);
//         start += ROT_SPEED / 4;
//     }
    
// }
