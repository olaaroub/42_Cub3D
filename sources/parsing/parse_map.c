/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:02:07 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/03 01:43:09 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map_bonus(t_map *map)
{
	int	i;

	i = 0;
	while (map->map_line[i])
	{
		if (map->map_line[i] == '\n' && (map->map_line[i + 1] == '\n'
			|| map->map_line[i + 1] == '\0'))
			return (0);
		if (map->map_line[i] != '1' && map->map_line[i] != '0'
			&& map->map_line[i] != ' ' && map->map_line[i] != '\n'
				&& map->map_line[i] != 'N' && map->map_line[i] != 'E'
					&& map->map_line[i] != 'W' && map->map_line[i] != 'S'
						&& map->map_line[i] != 'D' && map->map_line[i] != 'O'
							&& map->map_line[i] != 'F')
			return (0);
		i++;
	}
	return (1);
}

static int	check_map(t_map *map)
{
	int	i;

	i = 0;
	if(BONUS == 1)
		return(check_map_bonus(map));
	while (map->map_line[i])
	{
		if (map->map_line[i] == '\n' && (map->map_line[i + 1] == '\n'
			|| map->map_line[i + 1] == '\0'))
			return (0);
		if (map->map_line[i] != '1' && map->map_line[i] != '0'
			&& map->map_line[i] != ' ' && map->map_line[i] != '\n'
				&& map->map_line[i] != 'N' && map->map_line[i] != 'E'
					&& map->map_line[i] != 'W' && map->map_line[i] != 'S')
			return (0);
		i++;
	}
	return (1);
}

static void	get_game_elements(int fd, t_map *map)
{
	char	*line;
	t_list	*trash;

	trash = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		check_element(map, line);
	}
	skip_trailing_nl(map);
	close(fd);
	if (!check_map(map))
	{
		free_trash(&trash);
		ft_error("map invalid\n");
	}
	map->floor_color = ft_split(map->color, '\n');
	map->map = ft_split(map->map_line, '\n');
	map->texture = ft_split(map->texture_line, '\n');
	free_trash(&trash);
}

static void	check_player(char **map)
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
				ft_error("Multiple players!\n");
			else if (map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'N'
				|| map[i][j] == 'S')
				flag = 1;
			j++;
		}
		i++;
	}
	if (!flag)
		ft_error("No player!\n");
}

t_map   *read_map(char *file)
{
	int fd;
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		ft_error("Error: malloc failed\n");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("file not found\n");
	map->flag = 1;
	map->color = "";
	map->texture_line = "";
	map->map_line = "";
	get_game_elements(fd, map);
	check_player(map->map);
	check_if_surrounded(map->map);
	resize_map(map);
	return (map);
}
