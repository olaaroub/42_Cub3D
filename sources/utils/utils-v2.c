/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:40:20 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/06 18:52:42 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] && is_whitespace(line[i]))
		i++;
	j = i;
	while (line[j] && !is_whitespace(line[j]))
		j++;
	str = ft_substr(line, i, j - i);
	if (!ft_strcmp(str, "NO") || !ft_strcmp(str, "SO") || !ft_strcmp(str, "WE")
		|| !ft_strcmp(str, "EA"))
		return (free(str), 1);
	return (free(str), 0);
}

int	is_color(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] && is_whitespace(line[i]))
		i++;
	j = i;
	while (line[j] && !is_whitespace(line[j]))
		j++;
	str = ft_substr(line, i, j - i);
	if (!ft_strcmp(str, "F") || !ft_strcmp(str, "C"))
		return (free(str), 1);
	return (free(str), 0);
}

int	is_empty(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (!is_whitespace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_blocking_tile(char c)
{
	return (c == '1' || c == 'D' || c == 'F');
}
