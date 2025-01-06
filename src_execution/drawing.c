/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:32:59 by ohammou-          #+#    #+#             */
/*   Updated: 2024/12/28 15:27:53 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void initialization_the_angle()
{
	char **map;

	map = data_global()->map.map;
	if (map[data_global()->j][data_global()->i] == 'E')
		data_global()->angle = 0;
	else if (map[data_global()->j][data_global()->i] == 'W')
		data_global()->angle = PI;
	else if (map[data_global()->j][data_global()->i] == 'N')
		data_global()->angle = PI / 2;
	else if (map[data_global()->j][data_global()->i] == 'S')
		data_global()->angle = 3 * PI / 2;
}

void initialization_data_global()
{
	data_global()->i = data_global()->x;
	data_global()->j = data_global()->y;

	data_global()->x = (data_global()->x * SOF) + SOF / 3;
	data_global()->y = (data_global()->y * SOF) + SOF / 3;

    data_global()->fg_E = 0;
	data_global()->fg_W = 0;
    data_global()->fg_N = 0;
	data_global()->fg_S = 0;

    data_global()->fg_left = 0;
    data_global()->fg_right = 0;
	data_global()->is_vertical = false;
	initialization_the_angle();
}


void	main_of_drawing()
{
	t_img *img = malloc(sizeof(t_img));
	open_the_window();
	get_postion(data_global(), data_global()->map.map);
	initialization_data_global();
	get_data_addr(img);
	drawing(img);
	// drawing_rays(img);
	mlx_hook(data_global()->mlx_win, 17, 0,krwa, NULL);
	mlx_hook(data_global()->mlx_win, 2, 1L << 0, key_press, img);
	mlx_hook(data_global()->mlx_win, 3, 1L << 1, key_release, img);
}
