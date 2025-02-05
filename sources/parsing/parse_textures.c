/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 01:28:02 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/04 23:23:47 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ckeck_tex_path(t_data *data, char *str, char *path)
{
	if (!ft_strcmp(str, "NO"))
	{
		data->north_tex->path = ft_strdup(path);
		add_to_trash(&data->trash, data->north_tex->path);
	}
	else if (!ft_strcmp(str, "SO"))
	{
		data->south_tex->path = ft_strdup(path);
		add_to_trash(&data->trash, data->south_tex->path);
	}
	else if (!ft_strcmp(str, "WE"))
	{
		data->west_tex->path = ft_strdup(path);
		add_to_trash(&data->trash, data->west_tex->path);
	}
	else if (!ft_strcmp(str, "EA"))
	{
		data->east_tex->path = ft_strdup(path);
		add_to_trash(&data->trash, data->east_tex->path);
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
	data->north_tex = (t_texture *)malloc(sizeof(t_texture));
	data->south_tex = (t_texture *)malloc(sizeof(t_texture));
	data->west_tex = (t_texture *)malloc(sizeof(t_texture));
	data->east_tex = (t_texture *)malloc(sizeof(t_texture));
	data->north_tex->path = NULL;
	data->south_tex->path = NULL;
	data->west_tex->path = NULL;
	data->east_tex->path = NULL;
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
	if (i != 4 || !data->north_tex->path || !data->south_tex->path
		|| !data->west_tex->path || !data->east_tex->path)
		ft_error(data, "you have multiple texture args\n", 1);
}
