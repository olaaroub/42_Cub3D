/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 01:26:30 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/07 22:36:21 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	chack_if_valid(char **map, int i, int j)
{
	if (i == 0 || map[j][i - 1] == ' ')
		return (false);
	else if (map[j][i] && (map[j][i + 1] == ' ' || !map[j][i + 1]))
		return (false);
	else if (j >= 0 && (j == 0 || i > (int)ft_strlen(map[j - 1]) - 1 || map[j
				- 1][i] == ' '))
		return (false);
	else if ((map[j + 1] && map[j + 1][i] == ' ') || !map[j + 1]
		|| i > (int)ft_strlen(map[j + 1]) - 1)
		return (false);
	return (true);
}

bool	check_door(char **map, int i, int j)
{
	if ((map[j - 1][i] == '1' && map[j + 1][i] != '1') || (map[j][i - 1] == '1'
			&& map[j][i + 1] != '1'))
		return (false);
	if ((map[j - 1][i] == '0' && map[j + 1][i] != '0') || (map[j][i - 1] == '0'
			&& map[j][i + 1] != '0'))
		return (false);
	if ((map[j - 1][i] == '0' && map[j + 1][i] == '0') && (map[j][i - 1] == '0'
			&& map[j][i + 1] == '0'))
		return (false);
	if ((map[j - 1][i] == '1' && map[j + 1][i] == '1') && (map[j][i - 1] == '1'
			&& map[j][i + 1] == '1'))
		return (false);
	return (true);
}

bool	check_if_surrounded(t_data *data, char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if ((map[j][i] == '0' || map[j][i] == 'N' || map[j][i] == 'S'
				|| map[j][i] == 'E' || map[j][i] == 'W'
				|| (BONUS && map[j][i] == 'D')) && !chack_if_valid(map, i, j))
				ft_error(data, "Error:\ninvalid map222\n", 1);
			else if ((map[j][i] == 'D' && !check_door(map, i, j)) && BONUS)
				ft_error(data, "Error:\nwrong door placement\n", 1);
			i++;
		}
		j++;
	}
	return (true);
}
