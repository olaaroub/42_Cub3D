/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:02:07 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/29 16:49:38 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_element(t_map *map, char *line, t_list **trash)
{
	if (is_texture(line) && map->flag)
	{
		map->texture_line = ft_strjoin(map->texture_line, line);
		add_to_trash(map->texture_line, trash);
	}
	else if (is_color(line) && map->flag)
	{
		map->color = ft_strjoin(map->color, line);
		add_to_trash(map->color, trash);
	}
	else if (!is_empty(line) || !map->flag)
	{
		map->flag = 0;
		map->map_line = ft_strjoin(map->map_line, line);
		add_to_trash(map->map_line, trash);
	}
	free(line);
}

int	check_map_bonus(t_map *map)
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
						&& map->map_line[i] != 'D' && map->map_line[i] != 'O')
			return (0);
		i++;
	}
	return (1);
}


int	check_map(t_map *map)
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

void	skip_trailing_nl(t_map *map, t_list **trash)
{
	int len;
	char *str;

	len = ft_strlen(map->map_line) - 1;
	while (map->map_line[len] == '\n')
		len--;
	str = ft_substr(map->map_line, 0, len + 1);
	add_to_trash(str, trash);
	map->map_line = str;
}

void	get_game_elements(int fd, t_map *map)
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
	skip_trailing_nl(map, &trash);
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

void resize_map(t_map *map)
{
	int x_max;
	int j;
	int i;
	char *space;

	x_max = get_x_max(map->map);
	j = 0;
	while (map->map[j])
	{
		i = x_max - (int)ft_strlen(map->map[j]);
		if (i)
		{
			space = (char *)malloc(i + 1);
			space[i] = '\0';
			ft_memset(space, ' ', i);
			void *ptr = map->map[j];
			map->map[j] = ft_strjoin(map->map[j], space);
			free(ptr);
			free(space);
		}
		j++;
	}

}

t_map   read_map(char *file)
{
	int fd;
	t_map	map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("file not found\n");
	map.flag = 1;
	map.color = "";
	map.texture_line = "";
	map.map_line = "";
	get_game_elements(fd, &map);
	check_player(map.map);
	check_if_surrounded(map.map);

	resize_map(&map);
	return (map);
}
