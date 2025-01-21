/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:45:52 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/21 20:34:07 by ohammou-         ###   ########.fr       */
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

void set_color(t_data *data, char *name, char *color)
{
    char **sp;

    sp = ft_split(color, ',');
    if (count_coloumns(sp) != 3 || !is_valid_number(sp[0])
        || !is_valid_number(sp[1]) || !is_valid_number(sp[2])
        || cont_character(color, ',') != 2)
    {
        free_map(sp);
        ft_error("ERROR: you have a error in rgb color\n");
    }
    if (!ft_strcmp(name, "F"))
        data->map.floor_hex = rgb_to_hex(ft_atoi(sp[0]), ft_atoi(sp[1]), ft_atoi(sp[2]));
    else if (!ft_strcmp(name, "C"))
        data->map.ceiling_hex = rgb_to_hex(ft_atoi(sp[0]), ft_atoi(sp[1]), ft_atoi(sp[2]));
}

void skep_whitespace_to_color(t_data *data, int *j, int *cont, int i)
{
	while (data->map.floor_color[i][*j] && is_whitespace(data->map.floor_color[i][*j]))
		(*j)++;
	(*cont) = *j;
	while (data->map.floor_color[i][*cont] && !is_whitespace(data->map.floor_color[i][*cont]))
		(*cont)++;	

}

void pars_the_color(t_data *data)
{
    int i;
    int j;
    int cont;
    char *name;

    j = 0;
    while (data->map.floor_color[j])
    {
        i = 0;
        skep_whitespace_to_color(data, &i, &cont, j);
        name = ft_substr(data->map.floor_color[j], i, cont - i);
        i = cont;
        skep_whitespace_to_color(data, &i, &cont, j);
        set_color(data, name, ft_substr(data->map.floor_color[j], i, cont - i));
        i = cont;
    	skep_whitespace_to_color(data, &i, &cont, j);
		if (data->map.floor_color[j][i])
			ft_error("miltupl args in color\n");    
        j++;
    }
}
