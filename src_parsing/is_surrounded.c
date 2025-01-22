/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_surrounded.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:33:24 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/22 20:33:59 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool chack_if_valid(char **map, int i, int j)
{
    if (i == 0 || map[j][i - 1] == ' ')
        return false;
    else if (map[j][i] && (map[j][i + 1] == ' ' || !map[j][i + 1]))
        return false;
    else if (j >= 0 && (j == 0 || map[j - 1][i] == ' '))
        return false;
    else if ((map[j + 1] && map[j + 1][i] == ' ') || !map[j + 1])
        return false;
    return true;
}

bool check_if_surrounded(char **map)
{
    int i;
    int j;

    j = 0;
    while (map[j])
    {
        i = 0;
        while (map[j][i])
        {
            if ((map[j][i] == '0' || map[j][i] == 'N'
                || map[j][i] == 'S' || map[j][i] == 'E'
                || map[j][i] == 'W') && !chack_if_valid(map, i, j))
                ft_error("error: map not surrounded by wall\n");
            i++;
        }
        j++;
    }
    return true;
}
