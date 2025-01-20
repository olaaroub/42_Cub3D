/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:45:52 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/20 16:31:04 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int    rgb_to_hex(int r, int g, int b)
{
    if (r < 0)
        r = 0;
    if (r > 255)
        r = 255;
    if (g < 0)
        g = 0;
    if (g > 255)
        g = 255;
    if (b < 0)
        b = 0;
    if (b > 255)
        b = 255;
    return ((r << 16) | (g << 8) | b);
}

void set_color(t_data *data, char *floor, char *ceiling)
{
    char **spfloor;
    char **spceiling;

    spfloor = ft_split(floor, ',');
    spceiling = ft_split(ceiling, ',');
    if (ft_strlen_blm9lob(spfloor) != 3 || ft_strlen_blm9lob(spceiling) != 3)
        ft_error("error in rgb color\n");
    if (is_valid_number(spfloor[0]) && is_valid_number(spfloor[1])
        && is_valid_number(spfloor[2]))
        data->map.floor_hex = rgb_to_hex(atoi(spfloor[0]),atoi(spfloor[1]), atoi(spfloor[2]));
    else
        ft_error("error : floor color is invalid !\n");
    if (is_valid_number(spceiling[0]) && is_valid_number(spceiling[1])
        && is_valid_number(spceiling[2]))
        data->map.ceiling_hex = rgb_to_hex(atoi(spceiling[0]),atoi(spceiling[1]), atoi(spceiling[2]));
    else
        ft_error("error : ceiling color is invalid !\n");
}

void pars_the_color(t_data *data)
{
    char **first_color;
    char **secend_color;
    char *floor;
    char *ceiling;

    first_color  = ft_split(data->map.floor_color[0], ' ');
    secend_color = ft_split(data->map.floor_color[1], ' ');
    if (!ft_strcmp(first_color[0], "F"))
    {
        floor = first_color[1];
        ceiling = secend_color[1];
    }
    else
    {
        ceiling = first_color[1];
        floor = secend_color[1];
    }
    if (cont_character(floor, ',') != 2 || cont_character(ceiling, ',') != 2)
        ft_error("rgb error\n");
    set_color(data, floor, ceiling);
}
