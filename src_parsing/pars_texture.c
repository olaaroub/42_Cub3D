/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:39:45 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/21 02:02:32 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void check_ops(t_data *data, char **sp)
{
    if (!ft_strcmp(sp[0], "NO"))
        data->north_tex->path = ft_strdup(sp[1]);
    else if (!ft_strcmp(sp[0], "SO"))
        data->south_tex->path = ft_strdup(sp[1]);
    else if (!ft_strcmp(sp[0], "WE"))
        data->west_tex->path = ft_strdup(sp[1]);
    else if (!ft_strcmp(sp[0], "EA"))
        data->east_tex->path = ft_strdup(sp[1]);
    // printf("north = %s\n", data->north_tex->path);
    // printf("south = %s\n", data->south_tex->path);
    // printf("west = %s\n", data->west_tex->path);
    // printf("east = %s\n", data->east_tex->path);
}

void pars_texture(t_data *data)
{
    int i;
    char **sp;

    i = 0;
    data->north_tex = (t_texture*)malloc(sizeof(t_texture));
    data->south_tex = (t_texture*)malloc(sizeof(t_texture));
    data->west_tex = (t_texture*)malloc(sizeof(t_texture));
    data->east_tex = (t_texture*)malloc(sizeof(t_texture));
    while (data->map.texture[i])
    {
        sp = ft_split(data->map.texture[i], ' ');
        // for (size_t i = 0; i < 3; i++)
        // {
        //     printf("%s\n", sp[i]);
        // }

        if (ft_strlen_blm9lob(sp) != 2)
        {
            free_map(sp);
            ft_error("error: you dont have texture\n");
        }
        check_ops(data, sp);
        i++;
    }
}
