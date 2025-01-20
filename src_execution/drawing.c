/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:32:59 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/20 01:28:27 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void init_texture()
// {
// 	data_global()->north = (t_texture*)malloc(sizeof(t_texture));
// 	data_global()->north->texture = NULL;
// 	data_global()->north->addr = NULL;
// 	data_global()->north->bits_per_pixel = 0;
// 	data_global()->north->line_length = 0;
// 	data_global()->north->endian = 0;
// 	data_global()->north->width = 0;
// 	data_global()->north->height = 0;
// 	data_global()->north->path = ft_strdup("../imgs/text.xpm");
// 	data_global()->west = malloc(sizeof(t_texture));
// 	data_global()->east = malloc(sizeof(t_texture));
// 	data_global()->south = malloc(sizeof(t_texture));
// 	data_global()->north->texture = mlx_xpm_file_to_image(data_global()->mlx, data_global()->north->path,
// 			 &data_global()->north->width, &data_global()->north->height);
// 	if(!data_global()->north->texture)
// 	{
// 		printf("error\n");
// 		exit(1);
// 	}
// 	data_global()->north->addr = mlx_get_data_addr(data_global()->north->texture, &data_global()->north->bits_per_pixel,
// 			&data_global()->north->line_length, &data_global()->north->endian);
// 	data_global()->west->texture = mlx_xpm_file_to_image(data_global()->mlx, "../imgs/text.xpm",
// 			 &data_global()->west->width, &data_global()->west->height);
// 	data_global()->west->addr = mlx_get_data_addr(data_global()->west->texture, &data_global()->west->bits_per_pixel,
// 			&data_global()->west->line_length, &data_global()->west->endian);
// 	data_global()->east->texture = mlx_xpm_file_to_image(data_global()->mlx, "../imgs/text.xpm",
// 			 &data_global()->east->width, &data_global()->east->height);

// }

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
	data_global()->texture = (int*)malloc(64 * 64 * 4);
	// data_global()->south = (int*)malloc(64 * 64 * 4);
	// data_global()->east = (int*)malloc(64 * 64 * 4);
	// data_global()->west = (int*)malloc(64 * 64 * 4);
	int i = 0;
	int j = 0;

	while(i < 64)
	{
		j = 0;
		while(j < 64)
		{
			(data_global()->texture)[(j * 64) + i] = (i % 8 && j % 8) ? 0xFF0000FF : 0xFF000000;
			// (data_global()->south)[(j * 64) + i] = (i % 8 && j % 8) ? 0xFFFFFF00 : 0xFF000000;
			// (data_global()->east)[(j * 64) + i] = (i % 8 && j % 8) ? 0xFFFF0000 : 0xFF000000;
			// (data_global()->west)[(j * 64) + i] = (i % 8 && j % 8) ? 0xFF00FF00 : 0xFF000000;
			j++;
		}
		i++;
	}
	initialization_the_angle();
}


void	main_of_drawing()
{
	t_img *img = malloc(sizeof(t_img));
	open_the_window();
	get_postion(data_global(), data_global()->map.map);
	initialization_data_global();
	get_data_addr(img);
	// init_texture();
	// drawing(img);
	render_3d(img);
	mlx_hook(data_global()->mlx_win, 17, 0,krwa, NULL);
	mlx_hook(data_global()->mlx_win, 3, 1L << 1, key_release, img);
	mlx_hook(data_global()->mlx_win, 2, 1L << 0, key_press, img);
	mlx_loop_hook(data_global()->mlx, move, img);
}


