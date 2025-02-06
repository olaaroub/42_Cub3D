/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 01:28:02 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/06 02:52:31 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ckeck_tex_path(t_data *data, char *str, char *path)
{
	if (!ft_strcmp(str, "NO"))
	{
		N_TEX->path = ft_strdup(path);
		add_to_trash(&data->trash, N_TEX->path);
	}
	else if (!ft_strcmp(str, "SO"))
	{
		S_TEX->path = ft_strdup(path);
		add_to_trash(&data->trash, S_TEX->path);
	}
	else if (!ft_strcmp(str, "WE"))
	{
		W_TEX->path = ft_strdup(path);
		add_to_trash(&data->trash, W_TEX->path);
	}
	else if (!ft_strcmp(str, "EA"))
	{
		E_TEX->path = ft_strdup(path);
		add_to_trash(&data->trash, E_TEX->path);
	}
	free(str);
	free(path);
}

static void	skep_whitespace_to_texture(t_data *data, int *j, int *cont, int i)
{
	while (data->map->texture[i][*j]
		&& is_whitespace(data->map->texture[i][*j]))
		(*j)++;
	(*cont) = *j;
	while (data->map->texture[i][*cont]
		&& !is_whitespace(data->map->texture[i][*cont]))
		(*cont)++;
}

static void	initialize_textures(t_data *data)
{
	N_TEX = (t_texture *)malloc(sizeof(t_texture));
	S_TEX = (t_texture *)malloc(sizeof(t_texture));
	W_TEX = (t_texture *)malloc(sizeof(t_texture));
	E_TEX = (t_texture *)malloc(sizeof(t_texture));
	N_TEX->path = NULL;
	S_TEX->path = NULL;
	W_TEX->path = NULL;
	E_TEX->path = NULL;
}

void	pars_texture(t_data *data)
{
	int		cont;
	char	*sp;

	int (i), (j);
	i = 0;
	initialize_textures(data);
	while (data->map->texture[i])
	{
		j = 0;
		skep_whitespace_to_texture(data, &j, &cont, i);
		sp = ft_substr(data->map->texture[i], j, cont - j);
		j = cont;
		while (data->map->texture[i][j]
			&& is_whitespace(data->map->texture[i][j]))
			j++;
		cont = j;
		while (data->map->texture[i][cont])
			cont++;
		ckeck_tex_path(data, sp, ft_substr(data->map->texture[i], j, cont - j));
		j = cont;
		i++;
	}
	if (i != 4 || !N_TEX->path || !S_TEX->path
		|| !W_TEX->path || !E_TEX->path)
		ft_error(data, "you have multiple texture args\n", 1);
}
