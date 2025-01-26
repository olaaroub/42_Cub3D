/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:39:45 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/25 02:24:14 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/cub3d.h"

void check_ops(t_data *data, char *str, char *path)
{
	if (!ft_strcmp(str, "NO"))
		data->north_tex->path = ft_strdup(path);
	else if (!ft_strcmp(str, "SO"))
		data->south_tex->path = ft_strdup(path);
	else if (!ft_strcmp(str, "WE"))
		data->west_tex->path = ft_strdup(path);
	else if (!ft_strcmp(str, "EA"))
		data->east_tex->path = ft_strdup(path);
	free(str);
	free(path);
}

void skep_whitespace_to_texture(t_data *data, int *j, int *cont, int i)
{
	while (data->map.texture[i][*j] && is_whitespace(data->map.texture[i][*j]))
		(*j)++;
	(*cont) = *j;
	while (data->map.texture[i][*cont] && !is_whitespace(data->map.texture[i][*cont]))
		(*cont)++;
}

void initialize_textures(t_data *data)
{
	data->north_tex = (t_texture*)malloc(sizeof(t_texture));
	data->south_tex = (t_texture*)malloc(sizeof(t_texture));
	data->west_tex = (t_texture*)malloc(sizeof(t_texture));
	data->east_tex = (t_texture*)malloc(sizeof(t_texture));
	data->door_tex = (t_texture*)malloc(sizeof(t_texture));

	data->north_tex->path = NULL;
	data->south_tex->path = NULL;
	data->west_tex->path = NULL;
	data->east_tex->path = NULL;
	data->door_tex->path = NULL;
}

void pars_texture(t_data *data)
{
	int i;
	int j;
	int cont;
	char *sp;

	i = 0;
	initialize_textures(data);
	while (data->map.texture[i])
	{
		j = 0;
		skep_whitespace_to_texture(data, &j, &cont, i);
		sp = ft_substr(data->map.texture[i], j, cont - j);
		j = cont;
		while (data->map.texture[i][j] && is_whitespace(data->map.texture[i][j]))
		j++;
		cont = j;
		while (data->map.texture[i][cont])
			cont++;
		check_ops(data, sp, ft_substr(data->map.texture[i], j, cont - j));
		j = cont;
		i++;
	}
	if (i != 4 || !data->north_tex->path || !data->south_tex->path
		|| !data->west_tex->path || !data->east_tex->path)
		ft_error("you have multiple texture args\n");
}
