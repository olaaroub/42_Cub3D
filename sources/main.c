/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:51:29 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/30 18:21:39 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_argument(char **av, int ac, t_data *data)
{
    int i;

    if (ac != 2)
        exit(1);
    i = ft_strlen(av[1]);
    if (ft_strncmp(av[1] + i - 4, ".cub", 5) != 0)
        exit(1);
    data->map = read_map(av[1]);
    pars_the_color(data);
    pars_texture(data);
}

int    get_x_max(char **map)
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
	data->north_tex->texture = mlx_xpm_file_to_image(data->mlx, data->north_tex->path,
			 &data->north_tex->width, &data->north_tex->height);
    data->south_tex->texture = mlx_xpm_file_to_image(data->mlx, data->south_tex->path,
                &data->south_tex->width, &data->south_tex->height);
    data->east_tex->texture = mlx_xpm_file_to_image(data->mlx, data->east_tex->path,
                &data->east_tex->width, &data->east_tex->height);

    data->west_tex->texture = mlx_xpm_file_to_image(data->mlx, data->west_tex->path,
             &data->west_tex->width, &data->west_tex->height);

	if(!data->north_tex->texture || !data->south_tex->texture ||!data->west_tex->texture || !data->east_tex->texture)
        ft_error("Error\n: texture not found");
        //free_data(data); // this function is not implemented yet
	data->north_tex->addr = mlx_get_data_addr(data->north_tex->texture, &data->north_tex->bits_per_pixel,
			&data->north_tex->line_length, &data->north_tex->endian);
    data->south_tex->addr = mlx_get_data_addr(data->south_tex->texture, &data->south_tex->bits_per_pixel,
            &data->south_tex->line_length, &data->south_tex->endian);
    data->west_tex->addr = mlx_get_data_addr(data->west_tex->texture, &data->west_tex->bits_per_pixel,
            &data->west_tex->line_length, &data->west_tex->endian);
    data->east_tex->addr = mlx_get_data_addr(data->east_tex->texture, &data->east_tex->bits_per_pixel,
            &data->east_tex->line_length, &data->east_tex->endian);
    if(BONUS == 1)
    {
        // data->open_door_tex->texture = mlx_xpm_file_to_image(data->mlx, "images/open.xpm",
        //     &data->open_door_tex->width, &data->open_door_tex->height);
        data->door_tex[0].texture = mlx_xpm_file_to_image(data->mlx, "images/11.xpm",
            &data->door_tex[0].width, &data->door_tex[0].height);
        data->door_tex[1].texture = mlx_xpm_file_to_image(data->mlx, "images/22.xpm",
            &data->door_tex[1].width, &data->door_tex[1].height);
        data->door_tex[2].texture = mlx_xpm_file_to_image(data->mlx, "images/33.xpm",
            &data->door_tex[2].width, &data->door_tex[2].height);
        data->door_tex[3].texture = mlx_xpm_file_to_image(data->mlx, "images/44.xpm",
            &data->door_tex[3].width, &data->door_tex[3].height);


        // if(!data->open_door_tex->texture || !data->door_tex->texture)
        //     ft_error("Error\n: texture not found");
            //free_data(data); // this function is not implemented yet


        data->door_tex[0].addr = mlx_get_data_addr(data->door_tex[0].texture, &data->door_tex[0].bits_per_pixel,
            &data->door_tex[0].line_length, &data->door_tex[0].endian);
        data->door_tex[1].addr = mlx_get_data_addr(data->door_tex[1].texture, &data->door_tex[1].bits_per_pixel,
            &data->door_tex[1].line_length, &data->door_tex[1].endian);
        data->door_tex[2].addr = mlx_get_data_addr(data->door_tex[2].texture, &data->door_tex[2].bits_per_pixel,
            &data->door_tex[2].line_length, &data->door_tex[2].endian);
        data->door_tex[3].addr = mlx_get_data_addr(data->door_tex[3].texture, &data->door_tex[3].bits_per_pixel,
            &data->door_tex[3].line_length, &data->door_tex[3].endian);

        // data->open_door_tex->addr = mlx_get_data_addr(data->open_door_tex->texture, &data->open_door_tex->bits_per_pixel,
        //     &data->open_door_tex->line_length, &data->open_door_tex->endian);
    }
}

void    init_game(t_data *data)
{
    data->y_max = count_coloumns(data->map.map);
    data->x_max = ft_strlen(data->map.map[0]);
    get_postion(data, data->map.map);
	initialize_variables(data);
    data->mlx = mlx_init();
    data->mlx_win = mlx_new_window(data->mlx, SCREEN_W, SCREEN_H, "Cub3D");
    data->img = malloc(sizeof(t_img));
    data->img->img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
    data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bits_per_pixel,
                &data->img->line_length, &data->img->endian);
    init_texture(data);
}

static void	print_controls(void)
{
	printf(YELLOW "\n");
    printf("\t\t███    ███  █████  ██████  ███████ ██████   █████      ██████  ██ ██ ██ ██ ██   ██\n");
    printf("\t\t████  ████ ██   ██ ██   ██      ██ ██   ██ ██   ██     ██   ██ ██ ██ ██ ██ ██  ██\n");
    printf("\t\t██ ████ ██ ███████ ██████      ██  ██████  ███████     ██████  ██ ██ ██ ██ █████\n");
    printf("\t\t██  ██  ██ ██   ██ ██   ██    ██   ██   ██ ██   ██     ██   ██ ██ ██ ██ ██ ██  ██\n");
    printf("\t\t██      ██ ██   ██ ██   ██    ██   ██████  ██   ██     ██████  ██ ██ ██ ██ ██   ██\n");
	printf(RESET "\n");
	printf(RED "\t\t\tW A S D" RESET ": move\t");
	printf(RED "\t\t\t<| |>" RESET ": turn left / right\t\n");
	if (BONUS)
    {
		printf(RED "\t\t\tF" RESET ": open doors\t");
		printf(RED "\t\t\tE" RESET ": close doors\t\n");
		printf(RED "\t\t\tC" RESET ": animation (TODO)");
		printf(RED "\t\t\tMouse" RESET ": rotate view (TODO)\t");
    }
	printf("\n");
}


int main(int ac, char **av)
{
    t_data data;

    print_controls();
    check_argument(av, ac, &data);
    init_game(&data);
    main_of_drawing(&data);
    mlx_loop(data.mlx);
    return 0;
}