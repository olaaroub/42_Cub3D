/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:02:07 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/04 17:39:45 by olaaroub         ###   ########.fr       */
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

static void	get_game_elements(t_data *data, t_map *map, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		check_element(data, map, line);
	}
	// printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
	skip_trailing_nl(data, map);
	close(fd);
	if (!check_map(map))
	{

		ft_error(data,  "map invalid\n");
	}
	map->floor_color = ft_split(map->color, '\n');
	add_double_ptr_to_trash(data, (void **)map->floor_color);
	map->map = ft_split(map->map_line, '\n');
	add_double_ptr_to_trash(data, (void **)map->map);
	map->texture = ft_split(map->texture_line, '\n');
	add_double_ptr_to_trash(data, (void **)map->texture);
}

static void	check_player(t_data *data, char **map)
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
				ft_error(data,  "Multiple players!\n");
			else if (map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'N'
				|| map[i][j] == 'S')
				flag = 1;
			j++;
		}
		i++;
	}
	if (!flag)
		ft_error(data,  "No player!\n");
}

t_map   *read_map(t_data* data, char *file)
{
	int fd;
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		ft_error(data,  "Error: malloc failed\n");
	add_to_trash(&data->trash, map);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error(data,  "file not found\n");
	map->flag = 1;
	map->color = NULL;
	map->texture_line = NULL;
	map->map_line = NULL;
	get_game_elements(data, map, fd);
	check_player(data, map->map);
	check_if_surrounded(data, map->map);
	resize_map(data, map);
	return (map);
}
