/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:16:40 by ohammou-          #+#    #+#             */
/*   Updated: 2024/12/10 23:14:12 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int mouse(int botton,int key, int y, void *par)
{
    (void)key;
    (void)y;
    (void)par;
    // t_data *data = (t_data *)par;
    printf("%d\n", botton);
    // drawing_square(data, key, y, 10);
    return 0;
}

int esc(int key, void *param)
{
    (void)param;

    // t_data *data = param;
	if (key == 65307)
    {
        mlx_clear_window(data_global()->mlx, data_global()->mlx_win);
		exit(0);
    }
	return (0);
}

int	krwa()
{
	exit(0);
	return (0);
}