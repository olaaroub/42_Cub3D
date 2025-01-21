/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:39:45 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/21 20:26:13 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/cub3d.h"

char *remove_theHeadOfTexture(char *path)
{
	if (path[0] == '.' && path[1] == '/')
		return (ft_substr(path, 2, ft_strlen(path) - 2));
	return ft_strdup(path);
}

void check_ops(t_data *data, char *str, char *path)
{
	if (!ft_strcmp(str, "NO"))
		data->north_tex->path = remove_theHeadOfTexture(path);
	else if (!ft_strcmp(str, "SO"))
		data->south_tex->path = remove_theHeadOfTexture(path);
	else if (!ft_strcmp(str, "WE"))
		data->west_tex->path = remove_theHeadOfTexture(path);
	else if (!ft_strcmp(str, "EA"))
		data->east_tex->path = remove_theHeadOfTexture(path);
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

void pars_texture(t_data *data)
{
	int i;
	int j;
	int cont;
	char *sp;

	i = 0;
	data->north_tex = (t_texture*)malloc(sizeof(t_texture));
	data->south_tex = (t_texture*)malloc(sizeof(t_texture));
	data->west_tex = (t_texture*)malloc(sizeof(t_texture));
	data->east_tex = (t_texture*)malloc(sizeof(t_texture));
	while (data->map.texture[i])
	{
		j = 0;
		skep_whitespace_to_texture(data, &j, &cont, i);
		sp = ft_substr(data->map.texture[i], j, cont - j);
		j = cont;
		skep_whitespace_to_texture(data, &j, &cont, i);
		check_ops(data, sp, ft_substr(data->map.texture[i], j, cont - j));
		j = cont;
		skep_whitespace_to_texture(data, &j, &cont, i);
		if (data->map.texture[i][j])
			ft_error("miltupl args in texture\n");
		i++;
	}
	// printf("%s\n", data->east_tex->path);
}
