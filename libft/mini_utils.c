/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:10:19 by olaaroub          #+#    #+#             */
/*   Updated: 2024/12/01 17:38:31 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_whitespace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_isset(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	is_special_char(char c)
{
	if (c == '$' || c == '@' || c == '*' || c == '#' || c == '-' || c == '!'
		|| ft_isdigit(c))
		return (1);
	return (0);
}

int	words_len(char **words)
{
	int	i;

	i = 0;
	while (words[i])
		i++;
	return (i);
}
int	is_texture(char *line)
{
	return (ft_strnstr(line, "NO ", 3) || ft_strnstr(line, "SO ", 3)
		|| ft_strnstr(line, "WE ", 3) || ft_strnstr(line, "EA ", 3));
}

int	is_color(char *line)
{
	return (ft_strnstr(line, "F ", 2) || ft_strnstr(line, "C ", 2));
}
int is_emty(char *line)
{
	int i;

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