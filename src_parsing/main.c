/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:51:29 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/20 21:05:12 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void check_argument(char **av, int ac)
{
    int i;

    if (ac != 2)
        exit(1);
    i = ft_strlen(av[1]);
    if (ft_strncmp(av[1] + i - 4, ".cub", 5) != 0)
        exit(1);
}

int    get_x(char **map)
{
    int j;
    size_t nb;

    j = 0;
    nb = 0;
    while (map[j])
    {
        if (ft_strlen(map[j]) >= nb)
            nb = ft_strlen(map[j]);
        j++;
    }
    return nb;
}

void init_texture(t_data *data)
{
	data->north_tex = (t_texture*)malloc(sizeof(t_texture));
	// data->north_tex->path = ft_strdup("../imgs/text.xpm");
	data->north_tex->texture = mlx_xpm_file_to_image(data->mlx, "imgs/text.xpm",
			 &data->north_tex->width, &data->north_tex->height);
	if(!data->north_tex->texture)
	{
		printf("error\n");
		exit(1);
	}

	data->north_tex->addr = mlx_get_data_addr(data->north_tex->texture, &data->north_tex->bits_per_pixel,
			&data->north_tex->line_length, &data->north_tex->endian);
	// data->west->texture = mlx_xpm_file_to_image(data->mlx, "../imgs/text.xpm",
	// 		 &data->west->width, &data->west->height);
	// data->west->addr = mlx_get_data_addr(data->west->texture, &data->west->bits_per_pixel,
	// 		&data->west->line_length, &data->west->endian);
	// data->east->texture = mlx_xpm_file_to_image(data->mlx, "../imgs/text.xpm",
	// 		 &data->east->width, &data->east->height);

}

void    init_game(t_data *data, char **av)
{
    data->map = read_map(av[1]);
    pars_the_color(data); // this lines I added it her becose you will check parsing befor open the window
    pars_texture(data);
    data->mlx = mlx_init();
    data->mlx_win = mlx_new_window(data->mlx, SCREEN_W, SCREEN_H, "Cub3D");
    data->img = malloc(sizeof(t_img));
    data->img->img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
    data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bits_per_pixel,
                &data->img->line_length, &data->img->endian);
    data->y_max = ft_strlen_blm9lob(data->map.map);
    data->x_max = get_x(data->map.map);
    get_postion(data, data->map.map);
	initialize_variables(data);
    init_texture(data);

}

int main(int ac, char **av)
{
    t_data data;
    check_argument(av, ac);
    init_game(&data, av);
    main_of_drawing(&data);
    mlx_loop(data.mlx);
    return 0;
}