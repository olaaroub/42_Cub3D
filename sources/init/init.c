/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:16:37 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/06 03:29:41 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_texture(t_data *data)
{
	N_TEX->texture = XPM_IMG(data->mlx, N_TEX->path, &N_TEX->width,
			&N_TEX->height);
	S_TEX->texture = XPM_IMG(data->mlx, S_TEX->path, &S_TEX->width,
			&S_TEX->height);
	E_TEX->texture = XPM_IMG(data->mlx, E_TEX->path, &E_TEX->width,
			&E_TEX->height);
	W_TEX->texture = XPM_IMG(data->mlx, W_TEX->path, &W_TEX->width,
			&W_TEX->height);
	if (!N_TEX->texture || !S_TEX->texture || !W_TEX->texture
		|| !E_TEX->texture)
		ft_error(data, "Error: texture not found", 1);
	N_TEX->addr = ADDR(N_TEX->texture, &N_TEX->bpp, &N_TEX->line_len,
			&N_TEX->endian);
	S_TEX->addr = ADDR(S_TEX->texture, &S_TEX->bpp, &S_TEX->line_len,
			&S_TEX->endian);
	W_TEX->addr = ADDR(W_TEX->texture, &W_TEX->bpp, &W_TEX->line_len,
			&W_TEX->endian);
	E_TEX->addr = ADDR(E_TEX->texture, &E_TEX->bpp, &E_TEX->line_len,
			&E_TEX->endian);
}

static void	init_door_textures(t_data *data)
{
	int		curr;
	char	path[1024];

	curr = 1;
	D_TEX = malloc(sizeof(t_texture *) * DOOR_FRAMES);
	if (!D_TEX)
		ft_error(data, "Error: Malloc failed", 1);
	while (curr <= DOOR_FRAMES)
	{
		snprintf(path, sizeof(path), "imgs/door/%d.xpm", curr);
		D_TEX[curr - 1] = malloc(sizeof(t_texture));
		if (!D_TEX[curr - 1])
			ft_error(data, "Error: texture not found", 1);
		D_TEX[curr - 1]->texture = XPM_IMG(data->mlx, path,
				&D_TEX[curr - 1]->width, &D_TEX[curr - 1]->height);
		D_TEX[curr - 1]->addr = ADDR(D_TEX[curr - 1]->texture,
				&D_TEX[curr - 1]->bpp,
				&D_TEX[curr - 1]->line_len,
				&D_TEX[curr - 1]->endian);
		curr++;
	}
}

static void	init_hand_textures(t_data *data)
{
	int		curr;
	char	path[1024];

	curr = 1;
	H_TEX = malloc(sizeof(t_texture *) * HAND_FRAMES);
	if (!H_TEX)
		ft_error(data, "Error: Malloc failed", 1);
	while (curr <= HAND_FRAMES)
	{
		snprintf(path, sizeof(path), "imgs/anim/%d.xpm", curr);
		H_TEX[curr - 1] = malloc(sizeof(t_texture));
		if (!H_TEX[curr - 1])
			ft_error(data, "Error: texture not found", 1);
		H_TEX[curr - 1]->texture = XPM_IMG(data->mlx, path,
				&H_TEX[curr - 1]->width, &H_TEX[curr - 1]->height);
		H_TEX[curr - 1]->addr = ADDR(H_TEX[curr - 1]->texture,
				&H_TEX[curr - 1]->bpp,
				&H_TEX[curr - 1]->line_len,
				&H_TEX[curr - 1]->endian);
		curr++;
	}
}

static void	init_fire_textures(t_data *data)
{
	int		curr;
	char	path[1024];

	curr = 1;
	F_TEX = malloc(sizeof(t_texture *) * FIRE_FRAMES);
	if (!F_TEX)
		ft_error(data, "Error: Malloc failed", 1);
	while (curr <= FIRE_FRAMES)
	{
		snprintf(path, sizeof(path), "imgs/fire/f%d.xpm", curr);
		F_TEX[curr - 1] = malloc(sizeof(t_texture));
		if (!F_TEX[curr - 1])
			ft_error(data, "Error: texture not found", 1);
		F_TEX[curr - 1]->texture = XPM_IMG(data->mlx, path,
				&F_TEX[curr - 1]->width, &F_TEX[curr - 1]->height);
		F_TEX[curr - 1]->addr = ADDR(F_TEX[curr - 1]->texture,
				&F_TEX[curr - 1]->bpp,
				&F_TEX[curr - 1]->line_len,
				&F_TEX[curr - 1]->endian);
		curr++;
	}
}

void	init_game(t_data *data)
{
	data->y_max = count_coloumns(data->map->map);
	data->x_max = ft_strlen(data->map->map[0]);
	get_postion(data, data->map->map);
	initialize_variables(data);
	data->mlx = mlx_init();
	init_texture(data);
	if (BONUS)
	{
		init_door_textures(data);
		init_hand_textures(data);
		init_fire_textures(data);
		FRAMES = 0;
		HAND_CURR_FRAME = 0;
		FIRE_CURR_FRAME = 0;
	}
	data->mlx_win = mlx_new_window(data->mlx, SCREEN_W, SCREEN_H, "Cub3D");
	data->img = malloc(sizeof(t_img));
	data->img->img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
	data->img->addr = ADDR(data->img->img, &data->img->bpp,
			&data->img->line_len, &data->img->endian);
}
