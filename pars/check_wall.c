/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:03:02 by ohammou-          #+#    #+#             */
/*   Updated: 2024/09/10 10:33:40 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void check_wall(t_map *map)
{
    int i;
    int j;
    int len;

    i = 0;
    while (map->map[i])
    {
        j = 0;
        len = ft_strlen(map->map[i]) - 1;
        while (map->map[i][j] == ' ')
            j++;
        while (len && map->map[i][len] == ' ')
            len--;
        if (map->map[i][j] != '1' || map->map[i][len] != '1')
            ft_error("lmap mam9adach");
        i++;
    }
}

int ft_strlen_blm9lob(char **map)
{
    int len;

    len = 0;
    while (map[len])
        len++;
    return (len);
}

void check_wall2(t_map *map)
{
    char **mapp;
    t_data data;

    mapp = duplicate_map(map->map);
    get_postion(&data, mapp);
    flodfile(mapp, data.x, data.y);
    check_floodfile(mapp);
    free_map(mapp);
}
