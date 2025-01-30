/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:40:20 by olaaroub          #+#    #+#             */
/*   Updated: 2025/01/29 16:48:57 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixelput(t_img *img, int x, int y, int color)
{
	char	*tmp;

	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	tmp = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)tmp = color;
}

void    free_map(char **map)
{
    int i;

    i = 0;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}
int count_coloumns(char **map)
{
    int len;

    len = 0;
    while (map[len])
        len++;
    return (len);
}

