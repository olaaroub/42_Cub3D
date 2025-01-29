/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:36:09 by olaaroub          #+#    #+#             */
/*   Updated: 2025/01/29 02:04:51 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_postion(t_data *data, char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
		   if (map[j][i] == 'N' || map[j][i] == 'S'
			|| map[j][i] == 'E' || map[j][i] == 'W')
			{
				data->player_x = i;
				data->player_y = j;
				return ;
			}
			i++;
		}
		j++;
	}
}

char    **duplicate_map(char **map)
{
    int len;
    int i;
    char **map_v2;

    len = count_coloumns(map);
    map_v2 = malloc((len + 1) * sizeof(char *));
    i = 0;
    map_v2[len] = NULL;
    while (map[i])
    {
        map_v2[i] = ft_strdup(map[i]);
        i++;
    }
    return (map_v2);
}

t_data	*data_global()
{
	static t_data	data_gl;

	return (&data_gl);
}

void	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(1);
}