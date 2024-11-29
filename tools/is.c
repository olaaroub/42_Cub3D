/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:58:42 by ohammou-          #+#    #+#             */
/*   Updated: 2024/09/07 11:06:44 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_texture(char *line)
{
	return (ft_strnstr(line, "NO ", 3) || ft_strnstr(line, "SO ", 3)
		|| ft_strnstr(line, "WE ", 3) || ft_strnstr(line, "EA ", 3));
}

int	is_color(char *line)
{
	return (ft_strnstr(line, "F ", 2) || ft_strnstr(line, "C ", 2));
}

int	is_white_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int is_emty(char *line)
{
	int i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (!is_white_space(line[i]))
			return (0);
		i++;
	}
	return (1);
}