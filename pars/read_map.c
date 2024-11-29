/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:02:07 by ohammou-          #+#    #+#             */
/*   Updated: 2024/09/09 10:54:11 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void check_element(t_map *map, char *line, t_list **trash)
{
	if (is_texture(line) && map->flag)
	{
		map->textur_as_lien = ft_strjoin(map->textur_as_lien, line);
		add_to_trash(map->textur_as_lien, trash);
	}
	else if (is_color(line) && map->flag)
	{
		map->color = ft_strjoin(map->color, line);
		add_to_trash(map->color, trash);
	}
	else if (!is_emty(line) || !map->flag)
	{
		map->flag = 0;
		map->map_as_lien = ft_strjoin(map->map_as_lien, line);
		add_to_trash(map->map_as_lien, trash);
	}
	free(line);
}

int	check_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->map_as_lien[i])
	{
		if (map->map_as_lien[i] == '\n' && (map->map_as_lien[i + 1] == '\n'
			|| map->map_as_lien[i + 1] == '\0'))
			return (0);
		if (map->map_as_lien[i] != '1' && map->map_as_lien[i] != '0'
			&& map->map_as_lien[i] != ' ' && map->map_as_lien[i] != '\n'
				&& map->map_as_lien[i] != 'N' && map->map_as_lien[i] != 'E'
					&& map->map_as_lien[i] != 'W' && map->map_as_lien[i] != 'S')
			return (0);
		i++;
	}
	return (1);
}

void	skep_espace(t_map *map, t_list **trash)
{
	int len;
	char *str;

	len = ft_strlen(map->map_as_lien) - 1;
	while (map->map_as_lien[len] == '\n')
		len--;
	str = ft_substr(map->map_as_lien, 0, len + 1);
	add_to_trash(str, trash);
	map->map_as_lien = str;	
}

void	get_element_of_file(int fd, t_map *map)
{
	char	*line;
	t_list	*trash;

	trash = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		check_element(map, line, &trash);
	}
	skep_espace(map, &trash);
	close(fd);
	if (!check_map(map))
	{
		free_trash(&trash);
		ft_error("map invalid\n");
	}
	map->floor_color = ft_split(map->color, '\n');
	map->map = ft_split(map->map_as_lien, '\n');
	map->texture = ft_split(map->textur_as_lien, '\n');
	free_trash(&trash);
}

t_map   read_map(char *file)
{
	t_data	data;
	t_map	map;
	data.fd = open(file, O_RDONLY);
	map.flag = 1;
	map.color = "";
	map.textur_as_lien = "";
	map.map_as_lien = "";
	get_element_of_file(data.fd, &map);
	check_player(map.map);
	check_wall(&map);
	check_wall2(&map);
	return (map);
}
