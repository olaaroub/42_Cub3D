/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_postion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:18:08 by ohammou-          #+#    #+#             */
/*   Updated: 2024/09/09 21:24:07 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
				data->x = i;
				data->y = j;
				return ;
			}
			i++;
		}
		j++;
	}
}
