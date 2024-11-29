/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:14:08 by ohammou-          #+#    #+#             */
/*   Updated: 2024/10/12 10:39:20 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void move2(int key, int *x, int *y)
{
    if (key == 65363 && (*x != 40 || data_global()->map.map[data_global()->j][data_global()->i + 1] != '1'))
    {
        data_global()->x += 20;
        *x += 20;
    }
    else if (key == 65362 && (*y != 0 || data_global()->map.map[data_global()->j  - 1][data_global()->i] != '1'))
    {
        data_global()->y -= 20;
        *y -= 20;
    }
    else if (key == 65361 && (*x != 0 || data_global()->map.map[data_global()->j][data_global()->i - 1] != '1'))
    {
        data_global()->x -= 20;
        *x -= 20;
    }
    else if (key == 65364 && (*y != 40 || data_global()->map.map[data_global()->j  + 1][data_global()->i] != '1'))
    {
        data_global()->y += 20;
        *y += 20;
    }  
}

int move(int key, void *parm)
{
    static int x = 20;
    static int y = 20;

    if (key == 65363 && x == 40 && data_global()->map.map[data_global()->j][data_global()->i + 1] != '1')
    {
        data_global()->map.map[data_global()->j][data_global()->i + 1] = data_global()->map.map[data_global()->j][data_global()->i];
        data_global()->map.map[data_global()->j][data_global()->i] = '0';
        data_global()->i++;
        x = -20;
    }
    else if (key == 65361 && x == 0 && data_global()->map.map[data_global()->j][data_global()->i - 1] != '1')
    {
        data_global()->map.map[data_global()->j][data_global()->i - 1] = data_global()->map.map[data_global()->j][data_global()->i];
        data_global()->map.map[data_global()->j][data_global()->i] = '0';
        data_global()->i--;
        x = 60;
    }
    else if (key == 65362 && y == 0 && data_global()->map.map[data_global()->j - 1][data_global()->i] != '1')
    {
        data_global()->map.map[data_global()->j  - 1][data_global()->i] = data_global()->map.map[data_global()->j][data_global()->i];
        data_global()->map.map[data_global()->j][data_global()->i] = '0';
        data_global()->j--;
        y = 60;      
    }
    else if (key == 65364 && y == 40 && data_global()->map.map[data_global()->j + 1][data_global()->i] != '1')
    {
        data_global()->map.map[data_global()->j  + 1][data_global()->i] = data_global()->map.map[data_global()->j][data_global()->i];
        data_global()->map.map[data_global()->j][data_global()->i] = '0';
        data_global()->j++;
        y = -20;
    }
    move2(key, &x, &y);
    return 0;
}
