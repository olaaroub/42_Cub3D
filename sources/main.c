/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:51:29 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/06 23:28:12 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_argument(t_data *data, char **av, int ac)
{
	int	i;

	if (ac != 2)
		ft_error(data, "Error\n: invalid number of arguments\n", 1);
	data->minimap = malloc(sizeof(t_minimap));
	data->trash = NULL;
	add_to_trash(&data->trash, data->minimap);
	if (!data->minimap)
		return (printf("Error\n: malloc failed\n"), exit(1));
	i = ft_strlen(av[1]);
	if (ft_strncmp(av[1] + i - 4, ".cub", 5) != 0)
		return (ft_error(data, "Error\n: invalid file\n", 1));
	data->map = read_map(data, av[1]);
	pars_the_color(data);
	pars_texture(data);
}

static void	complete_priniting(void)
{
	printf("\t\t |   |    ██║   ██║   ██║    ██║ \
    ██║   ██║██████╔╝ █████╔╝██║  ██║ |   |\n");
	printf("\t\t |   |    ██║   ██║   ██║    ██║ \
    ██║   ██║██╔══██╗ ╚═══██╗██║  ██║ |   |\n");
	printf("\t\t |   |    ██║   ╚██████╔╝    ╚███\
███╗╚██████╔╝██████╔╝██████╔╝██████╔╝ |   |\n");
	printf("\t\t |   |    ╚═╝    ╚═════╝      ╚══\
═══╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝  |   |\n");
	printf("\t\t |___|                           \
                                      |___|\n");
	printf("\t\t(_____)--------------------------\
-------------------------------------(_____)\n");
	printf(RESET BOLD"\n");
	printf(RED "\t\t\tW A S D" RESET BOLD": move\t");
	printf(RED "\t\t\t<| |>" RESET BOLD": turn left / right\t\n");
	if (BONUS)
	{
		printf(RED "\t\t\tF" RESET BOLD": open doors\t");
		printf(RED "\t\t\tE" RESET BOLD": close doors\t\n");
		printf(RED "\t\t\t\t\tMouse" RESET BOLD": rotate view\t");
	}
	printf("\n" RESET);
}

static void	print_controls(void)
{
	printf(BOLD YELLOW "\n");
	printf("\t\t _____                           \
                                      _____\n");
	printf("\t\t( ___ )--------------------------\
-------------------------------------( ___ )\n");
	printf("\t\t |   |                           \
                                      |   |\n");
	printf("\t\t |   | ██╗    ██╗███████╗██╗     \
 ██████╗ ██████╗ ███╗   ███╗███████╗  |   |\n");
	printf("\t\t |   | ██║    ██║██╔════╝██║     \
██╔════╝██╔═══██╗████╗ ████║██╔════╝  |   |\n");
	printf("\t\t |   | ██║ █╗ ██║█████╗  ██║     \
██║     ██║   ██║██╔████╔██║█████╗    |   |\n");
	printf("\t\t |   | ██║███╗██║██╔══╝  ██║     \
██║     ██║   ██║██║╚██╔╝██║██╔══╝    |   |\n");
	printf("\t\t |   | ╚███╔███╔╝███████╗███████╗\
╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗  |   |\n");
	printf("\t\t |   |  ╚══╝╚══╝ ╚══════╝╚══════╝\
 ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝  |   |\n");
	printf("\t\t |   | ████████╗ ██████╗      ███\
███╗██╗   ██╗██████╗ ██████╗ ██████╗  |   |\n");
	printf("\t\t |   | ╚══██╔══╝██╔═══██╗    ██╔═\
═══╝██║   ██║██╔══██╗╚════██╗██╔══██╗ |   |\n");
	complete_priniting();
}

int	main(int ac, char **av)
{
	t_data	data;

	data.mlx = NULL;
	data.mlx_win = NULL;
	check_argument(&data, av, ac);
	init_game(&data);
	print_controls();
	game_loop(&data);
	mlx_loop(data.mlx);
	return (0);
}
