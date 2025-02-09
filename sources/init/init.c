/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:16:37 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/09 22:27:26 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_texture(t_data *data)
{
	data->n_tex->texture = XPM_IMG(data->mlx, data->n_tex->path,
			&data->n_tex->width, &data->n_tex->height);
	data->s_tex->texture = XPM_IMG(data->mlx, data->s_tex->path,
			&data->s_tex->width, &data->s_tex->height);
	data->e_tex->texture = XPM_IMG(data->mlx, data->e_tex->path,
			&data->e_tex->width, &data->e_tex->height);
	data->w_tex->texture = XPM_IMG(data->mlx, data->w_tex->path,
			&data->w_tex->width, &data->w_tex->height);
	if (!data->n_tex->texture || !data->s_tex->texture
		|| !data->w_tex->texture || !data->e_tex->texture)
		ft_error(data, "Error:\ntexture not found\n", 1);
	data->n_tex->addr = ADDR(data->n_tex->texture, &data->n_tex->bpp,
			&data->n_tex->line_len, &data->n_tex->endian);
	data->s_tex->addr = ADDR(data->s_tex->texture, &data->s_tex->bpp,
			&data->s_tex->line_len, &data->s_tex->endian);
	data->w_tex->addr = ADDR(data->w_tex->texture, &data->w_tex->bpp,
			&data->w_tex->line_len, &data->w_tex->endian);
	data->e_tex->addr = ADDR(data->e_tex->texture, &data->e_tex->bpp,
			&data->e_tex->line_len, &data->e_tex->endian);
}

static void	init_door_textures(t_data *data)
{
	int		curr;
	char	path[1024];

	curr = 1;
	data->anim->d_tex = malloc(sizeof(t_texture *) * DOOR_FRAMES);
	if (!data->anim->d_tex)
		ft_error(data, "Error:\nMalloc failed\n", 1);
	while (curr <= DOOR_FRAMES)
	{
		snprintf(path, sizeof(path), "imgs/door/%d.xpm", curr);
		data->anim->d_tex[curr - 1] = malloc(sizeof(t_texture));
		if (!data->anim->d_tex[curr - 1])
			ft_error(data, "Error:\ntexture not found\n", 1);
		add_to_trash(&data->trash, data->anim->d_tex[curr - 1]);
		data->anim->d_tex[curr - 1]->texture = XPM_IMG(data->mlx, path,
				&data->anim->d_tex[curr - 1]->width,
				&data->anim->d_tex[curr - 1]->height);
		data->anim->d_tex[curr - 1]->addr = ADDR(
				data->anim->d_tex[curr - 1]->texture,
				&data->anim->d_tex[curr - 1]->bpp,
				&data->anim->d_tex[curr - 1]->line_len,
				&data->anim->d_tex[curr - 1]->endian);
		curr++;
	}
}

static void	init_hand_textures(t_data *data)
{
	int		curr;
	char	path[1024];

	curr = 1;
	data->anim->h_tex = malloc(sizeof(t_texture *) * HAND_FRAMES);
	if (!data->anim->h_tex)
		ft_error(data, "Error:\nMalloc failed\n", 1);
	while (curr <= HAND_FRAMES)
	{
		snprintf(path, sizeof(path), "imgs/anim/%d.xpm", curr);
		data->anim->h_tex[curr - 1] = malloc(sizeof(t_texture));
		if (!data->anim->h_tex[curr - 1])
			ft_error(data, "Error:\ntexture not found\n", 1);
		add_to_trash(&data->trash, data->anim->h_tex[curr - 1]);
		data->anim->h_tex[curr - 1]->texture = XPM_IMG(data->mlx, path,
				&data->anim->h_tex[curr - 1]->width,
				&data->anim->h_tex[curr - 1]->height);
		data->anim->h_tex[curr - 1]->addr = ADDR(
				data->anim->h_tex[curr - 1]->texture,
				&data->anim->h_tex[curr - 1]->bpp,
				&data->anim->h_tex[curr - 1]->line_len,
				&data->anim->h_tex[curr - 1]->endian);
		curr++;
	}
}

static void	init_fire_textures(t_data *data)
{
	int		curr;
	char	path[1024];

	curr = 1;
	data->anim->f_tex = malloc(sizeof(t_texture *) * FIRE_FRAMES);
	if (!data->anim->f_tex)
		ft_error(data, "Error:\nMalloc failed\n", 1);
	while (curr <= FIRE_FRAMES)
	{
		snprintf(path, sizeof(path), "imgs/fire/f%d.xpm", curr);
		data->anim->f_tex[curr - 1] = malloc(sizeof(t_texture));
		if (!data->anim->f_tex[curr - 1])
			ft_error(data, "Error:\ntexture not found\n", 1);
		add_to_trash(&data->trash, data->anim->f_tex[curr - 1]);
		data->anim->f_tex[curr - 1]->texture = XPM_IMG(data->mlx, path,
				&data->anim->f_tex[curr - 1]->width,
				&data->anim->f_tex[curr - 1]->height);
		data->anim->f_tex[curr - 1]->addr = ADDR(
				data->anim->f_tex[curr - 1]->texture,
				&data->anim->f_tex[curr - 1]->bpp,
				&data->anim->f_tex[curr - 1]->line_len,
				&data->anim->f_tex[curr - 1]->endian);
		curr++;
	}
}

void	init_game(t_data *data)
{
	data->y_max = words_len(data->map->map);
	data->x_max = ft_strlen(data->map->map[0]);
	get_postion(data, data->map->map);
	initialize_variables(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_error(data, "Error:\nmlx failed\n", 1);
	init_texture(data);
	if (BONUS)
	{
		init_door_textures(data);
		init_hand_textures(data);
		init_fire_textures(data);
		data->anim->d_curr = 0;
		data->anim->h_curr = 0;
		data->anim->f_curr = 0;
	}
	data->mlx_win = mlx_new_window(data->mlx, SCREEN_W, SCREEN_H, "Cub3D");
	data->img = malloc(sizeof(t_img));
	add_to_trash(&data->trash, data->img);
	data->img->img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
	if (!data->mlx_win || !data->img->img)
		ft_error(data, "Error:\nmlx failed\n", 1);
	data->img->addr = ADDR(data->img->img, &data->img->bpp,
			&data->img->line_len, &data->img->endian);
}
