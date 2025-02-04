/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:45:52 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/04 16:32:35 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

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

int strlen_scipingziro(char *str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (str[i] && str[i] == '0')
		i++;
	while (str[i++])
		len++;
	return len;
}

void set_color(t_data *data, char *name, char *color)
{
	char **sp;
	char *red;
	char *green;
	char *blue;

	sp = ft_split(color, ',');
	if (count_coloumns(sp) != 3)
		ft_error(data,  "invalid colors!\n");
	red = ft_strtrim(sp[0], "\n\t ");
	green = ft_strtrim(sp[1], "\n\t ");
	blue = ft_strtrim(sp[2], "\n\t ");
	if (!is_valid_number(red) || !is_valid_number(green) || !is_valid_number(blue)
		|| count_chars(color, ',') != 2)
		ft_error(data,  "invalid colors!\n");
	if (strlen_scipingziro(red) > 3 || strlen_scipingziro(green) > 3
		|| strlen_scipingziro(blue) > 3)
		ft_error(data,  "invalid colors!\n");
	if (!ft_strcmp(name, "F"))
		data->map->floor_hex = rgb_to_hex(ft_atoi(red), ft_atoi(green), ft_atoi(blue));
	else if (!ft_strcmp(name, "C"))
		data->map->ceiling_hex = rgb_to_hex(ft_atoi(red), ft_atoi(green), ft_atoi(blue));
	free(red);
	free(green);
	free(blue);
}

void pars_the_color(t_data *data)
{
	int i;
	int j;

	j = 0;
	data->map->ceiling_hex = -1;
	data->map->floor_hex = -1;
	while (data->map->floor_color[j])
	{
		i = 0;
		while (data->map->floor_color[j][i] && is_whitespace(data->map->floor_color[j][i]))
			i++;
		if (data->map->floor_color[j][i] == 'F' && data->map->floor_color[j][i + 1])
			set_color(data, "F", &data->map->floor_color[j][i + 1]);
		else if (data->map->floor_color[j][i] == 'C' && data->map->floor_color[j][i + 1])
			set_color(data, "C", &data->map->floor_color[j][i + 1]);
		else
			ft_error(data,  "Enter a valid color!\n");
		j++;
	}
	if (j != 2 || data->map->ceiling_hex == -1 || data->map->floor_hex == -1)
		ft_error(data,  "Enter a valid color!\n");
}
