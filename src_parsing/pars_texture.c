/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:39:45 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/20 19:07:46 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void check_ops(t_data *data, char **sp)
{
    if (!ft_strcmp(sp[0], "WE"))
        data->map.texturOfWe = ft_strdup(sp[1]);
    else if (!ft_strcmp(sp[0], "NO"))
        data->map.texturOfNo = ft_strdup(sp[1]);
    else if (!ft_strcmp(sp[0], "EA"))
        data->map.texturOfEa = ft_strdup(sp[1]);
    else if (!ft_strcmp(sp[0], "SO"))
        data->map.texturOfSo = ft_strdup(sp[1]);    
}

void pars_texture(t_data *data)
{
    int i;
    char **sp;

    i = 0;
    while (data->map.texture[i])
    {
        sp = ft_split(data->map.texture[i], ' ');
        if (ft_strlen_blm9lob(sp) != 2)
        {
            free_map(sp);
            ft_error("error: you dont have textur\n");
        }
        check_ops(data, sp);
        i++;
    }
}
