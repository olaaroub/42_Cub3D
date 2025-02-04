/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:35:48 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/04 17:38:19 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int    get_x_max(char **map)
{
    int j;
    size_t nb;

    j = 0;
    nb = 0;
    while (map[j])
    {
        if (ft_strlen(map[j]) >= nb)
            nb = ft_strlen(map[j]);
        j++;
    }
    return nb;
}

void	skip_trailing_nl(t_data *data, t_map *map)
{
	int len;
	char *str;

	len = ft_strlen(map->map_line) - 1;
	while (map->map_line[len] == '\n')
		len--;
	str = ft_substr(map->map_line, 0, len + 1);
	// free(map->map_line);
	add_to_trash(&data->trash, str);
	map->map_line = str;

}

void resize_map(t_data *data, t_map *map)
{
	int x_max;
	int j;
	int i;
	char *space;
	(void)data;

	x_max = get_x_max(map->map);
	j = 0;
	while (map->map[j])
	{
		i = x_max - (int)ft_strlen(map->map[j]);
		if (i)
		{
			space = (char *)malloc(i + 1);
			space[i] = '\0';
			ft_memset(space, ' ', i);
			// void *ptr = map->map[j];
			map->map[j] = ft_strjoin(map->map[j], space);
			add_to_trash(&data->trash, map->map[j]);
			// free(ptr);
			free(space);
		}
		j++;
	}
}

void check_element(t_data* data, t_map *map, char *line)
{
	(void)data;
	if (is_texture(line) && map->flag)
	{
		map->texture_line = ft_strjoin(map->texture_line, line);
		add_to_trash(&data->trash, map->texture_line);
	}
	else if (is_color(line) && map->flag)
	{
		map->color = ft_strjoin(map->color, line);
		add_to_trash(&data->trash, map->color);
	}
	else if (!is_empty(line) || !map->flag)
	{
		map->flag = 0;
		map->map_line = ft_strjoin(map->map_line, line);
		add_to_trash(&data->trash, map->map_line);
	}
	free(line);
}


