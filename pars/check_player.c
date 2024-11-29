/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:39:45 by ohammou-          #+#    #+#             */
/*   Updated: 2024/09/10 10:47:29 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_player(char **map)
{
	int	i;
	int	flag;
	int j;

	flag = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'N'
				|| map[i][j] == 'S') && flag == 1)
				ft_error("multiple player\n");
			else if (map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'N'
				|| map[i][j] == 'S')
				flag = 1;
			j++;
		}
		i++;
	}
	if (!flag)
		ft_error("no player !\n");
}
