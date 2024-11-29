/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:16:40 by ohammou-          #+#    #+#             */
/*   Updated: 2024/10/10 20:31:40 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int mouse(int botton,int key, int y, void *par)
{
    t_data *data = (t_data *)par;

    printf("%d\n", botton);
    // drawing_square(data, key, y, 10);
    return 0;
}

int esc(int key, void *param)
{
    t_data *data = param;
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