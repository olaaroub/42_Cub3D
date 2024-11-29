/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:31:54 by ohammou-          #+#    #+#             */
/*   Updated: 2024/09/08 15:46:01 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char    **duplicate_map(char **map)
{
    int len;
    int i;
    char **map_v2;

    len = ft_strlen_blm9lob(map);
    map_v2 = malloc((len + 1) * sizeof(char *));
    i = 0;
    map_v2[len] = NULL;
    while (map[i])
    {
        map_v2[i] = ft_strdup(map[i]);
        i++;
    }
    return (map_v2);
}