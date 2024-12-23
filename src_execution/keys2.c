/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:14:08 by ohammou-          #+#    #+#             */
/*   Updated: 2024/12/23 22:02:08 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


int move(int key, void *parm)
{

    int x = data_global()->x;
    int y = data_global()->y;
    char **map = data_global()->map.map;

    (void)parm;
    printf("x: %d  y: %d\n", x, y);
    if(key == RIGHT && map[y / SOF][(x + SOP + FRM - 1) / SOF] != '1' && map[(y + SOP - 1) / SOF][(x + SOP + FRM - 1) / SOF] != '1')
        data_global()->x += FRM;
    if (key == LEFT && map[y / SOF][(x - FRM) / SOF] != '1' && map[(y + SOP - 1) / SOF][(x - FRM) / SOF] != '1')
        data_global()-> x -= FRM;
    if (key == DOWN && map[(y + SOP + FRM - 1) / SOF][x / SOF] != '1' && map[(y + SOP + FRM - 1) / SOF][(x + SOP - 1) / SOF] != '1')
        data_global()->y += FRM;
    if (key == UP && map[(y - FRM ) / SOF][x / SOF] != '1' && map[(y - FRM) / SOF][(x + SOP - 1) / SOF] != '1')
        data_global()->y -= FRM;
    printf("x: %d  y: %d\n", x, y);

    return 0;
}


