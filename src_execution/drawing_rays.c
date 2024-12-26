/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:12:01 by ohammou-          #+#    #+#             */
/*   Updated: 2024/12/26 19:59:57 by ohammou-         ###   ########.fr       */
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


int drawing_ray(t_img *img)
{
    int x_start = data_global()->x + SOP / 2;
    int y_start = data_global()->y + SOP / 2;

    int ray_length = 100; // Length of the ray
    int x_end = x_start + ray_length * cos(data_global()->angle);
    int y_end = y_start - ray_length * sin(data_global()->angle);

    // Interpolate and draw the line from (x_start, y_start) to (x_end, y_end)
    int dx = x_end - x_start;
    int dy = y_end - y_start;
    int steps = 0; // Determine the number of steps
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
        ft_pixelput(img, (int)x, (int)y, 0x00FF00); // Draw pixel
        x += x_inc;
        y += y_inc;
        i++;
    }
    i = 0;
    x = x_start;
    y = y_start;
    while (i <= steps) 
    {
        ft_pixelput(img, (int)x, (int)y, 0x0000FF); // Draw pixel
        x -= x_inc;
        y -= y_inc;
        i++;
    }
    // printf("Ray endpoint: x: %d    y: %d\n", x_end, y_end);
    return 0;
}
