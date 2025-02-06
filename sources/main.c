/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:51:29 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/06 03:16:29 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_argument(t_data *data, char **av, int ac)
{
	int	i;

	if (ac != 2)
		exit(1);
	data->minimap = malloc(sizeof(t_minimap));
	data->trash = NULL;
	add_to_trash(&data->trash, data->minimap);
	if (!data->minimap)
		return (printf("Error\n: malloc failed\n"), exit(1));
	i = ft_strlen(av[1]);
	if (ft_strncmp(av[1] + i - 4, ".cub", 5) != 0)
		return (ft_error(data, "Error\n: file not valid\n", 1));
	data->map = read_map(data, av[1]);
	pars_the_color(data);
	pars_texture(data);
}

static void	print_controls(void)
{
	printf(YELLOW "\n");
	printf("\t\t███    ███  █████  ██████  ███████ \
    ██████   █████      ██████  ██ ██ ██ ██ ██   ██\n");
	printf("\t\t████  ████ ██   ██ ██   ██      ██ \
    ██   ██ ██   ██     ██   ██ ██ ██ ██ ██ ██  ██\n");
	printf("\t\t██ ████ ██ ███████ ██████      ██  \
    ██████  ███████     ██████  ██ ██ ██ ██ █████\n");
	printf("\t\t██  ██  ██ ██   ██ ██   ██    ██   \
    ██   ██ ██   ██     ██   ██ ██ ██ ██ ██ ██  ██\n");
	printf("\t\t██      ██ ██   ██ ██   ██    ██   \
    ██████  ██   ██     ██████  ██ ██ ██ ██ ██   ██\n");
	printf(RESET "\n");
	printf(RED "\t\t\tW A S D" RESET ": move\t");
	printf(RED "\t\t\t<| |>" RESET ": turn left / right\t\n");
	if (BONUS)
	{
		printf(RED "\t\t\tF" RESET ": open doors\t");
		printf(RED "\t\t\tE" RESET ": close doors\t\n");
		printf(RED "\t\t\tC" RESET ": animation (TODO)");
		printf(RED "\t\t\tMouse" RESET ": rotate view (TODO)\t");
	}
	printf("\n");
}

int	main(int ac, char **av)
{
	t_data	data;

	print_controls();
	data.mlx = NULL;
	check_argument(&data, av, ac);
	init_game(&data);
	game_loop(&data);
	mlx_loop(data.mlx);
	return (0);
}
