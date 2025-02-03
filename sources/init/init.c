/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:16:37 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/03 01:24:16 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_texture(t_data *data)
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
        ft_error("Error: texture not found");
	data->north_tex->addr = mlx_get_data_addr(data->north_tex->texture, &data->north_tex->bits_per_pixel,
			&data->north_tex->line_length, &data->north_tex->endian);
    data->south_tex->addr = mlx_get_data_addr(data->south_tex->texture, &data->south_tex->bits_per_pixel,
            &data->south_tex->line_length, &data->south_tex->endian);
    data->west_tex->addr = mlx_get_data_addr(data->west_tex->texture, &data->west_tex->bits_per_pixel,
            &data->west_tex->line_length, &data->west_tex->endian);
    data->east_tex->addr = mlx_get_data_addr(data->east_tex->texture, &data->east_tex->bits_per_pixel,
            &data->east_tex->line_length, &data->east_tex->endian);
}

static void init_door_textures(t_data *data)
{
    int current_frame = 1;
    char path[1024];

    data->animations->door_tex = malloc(sizeof(t_texture *) * DOOR_FRAMES);
    if (!data->animations->door_tex)
        ft_error("Error: Malloc failed");
    while (current_frame <= DOOR_FRAMES)
    {
        snprintf(path, sizeof(path), "imgs/door/%d.xpm", current_frame);
        data->animations->door_tex[current_frame - 1] = malloc(sizeof(t_texture));
        if (!data->animations->door_tex[current_frame - 1])
            ft_error("Error: texture not found");
        data->animations->door_tex[current_frame - 1]->texture = mlx_xpm_file_to_image(data->mlx,
                path, &data->animations->door_tex[current_frame - 1]->width,
                &data->animations->door_tex[current_frame - 1]->height);
        data->animations->door_tex[current_frame - 1]->addr = mlx_get_data_addr(data->animations->door_tex[current_frame - 1]->texture,
                &data->animations->door_tex[current_frame - 1]->bits_per_pixel,
                &data->animations->door_tex[current_frame - 1]->line_length,
                &data->animations->door_tex[current_frame - 1]->endian);
        current_frame++;
    }
}

static void    init_hand_textures(t_data *data)
{
    int current_frame = 1;
    char path[1024];

    data->animations->hand_tex = malloc(sizeof(t_texture *) * HAND_FRAMES);
    if (!data->animations->hand_tex)
        ft_error("Error: Malloc failed");
    while (current_frame <= HAND_FRAMES)
    {
        snprintf(path, sizeof(path), "imgs/anim/%d.xpm", current_frame);
        data->animations->hand_tex[current_frame - 1] = malloc(sizeof(t_texture));
        if (!data->animations->hand_tex[current_frame - 1])
            ft_error("Error: texture not found");
        data->animations->hand_tex[current_frame - 1]->texture = mlx_xpm_file_to_image(data->mlx,
                path, &data->animations->hand_tex[current_frame - 1]->width,
                &data->animations->hand_tex[current_frame - 1]->height);
        data->animations->hand_tex[current_frame - 1]->addr = mlx_get_data_addr(data->animations->hand_tex[current_frame - 1]->texture,
                &data->animations->hand_tex[current_frame - 1]->bits_per_pixel,
                &data->animations->hand_tex[current_frame - 1]->line_length,
                &data->animations->hand_tex[current_frame - 1]->endian);
        current_frame++;
    }
}

static void    init_fire_textures(t_data *data)
{
    int current_frame = 1;
    char path[1024];

    data->animations->fire_tex = malloc(sizeof(t_texture *) * FIRE_FRAMES);
    if (!data->animations->fire_tex)
        ft_error("Error: Malloc failed");
    while (current_frame <= FIRE_FRAMES)
    {
        snprintf(path, sizeof(path), "imgs/fire/f%d.xpm", current_frame);
        data->animations->fire_tex[current_frame - 1] = malloc(sizeof(t_texture));
        if (!data->animations->fire_tex[current_frame - 1])
            ft_error("Error: texture not found");
        data->animations->fire_tex[current_frame - 1]->texture = mlx_xpm_file_to_image(data->mlx,
                path, &data->animations->fire_tex[current_frame - 1]->width,
                &data->animations->fire_tex[current_frame - 1]->height);
        FIRE_TEX[current_frame - 1]->addr = mlx_get_data_addr(FIRE_TEX[current_frame - 1]->texture,
                &data->animations->fire_tex[current_frame - 1]->bits_per_pixel,
                &data->animations->fire_tex[current_frame - 1]->line_length,
                &data->animations->fire_tex[current_frame - 1]->endian);
        current_frame++;
    }
}

void    init_game(t_data *data)
{
    data->y_max = count_coloumns(data->map->map);
    data->x_max = ft_strlen(data->map->map[0]);
    get_postion(data, data->map->map);
	initialize_variables(data);
    data->mlx = mlx_init();
    init_texture(data);
    if(BONUS)
    {
        init_door_textures(data);
        init_hand_textures(data);
        init_fire_textures(data);
    }
    data->mlx_win = mlx_new_window(data->mlx, SCREEN_W, SCREEN_H, "Cub3D");
    data->img = malloc(sizeof(t_img));
    data->img->img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
    data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bits_per_pixel,
                &data->img->line_length, &data->img->endian);
}