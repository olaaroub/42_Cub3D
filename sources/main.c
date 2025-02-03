/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:51:29 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/03 18:13:58 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void check_argument(char **av, int ac, t_data *data)
{
    int i;

    if (ac != 2)
        exit(1);
    data->map = malloc(sizeof(t_map));
    data->minimap = malloc(sizeof(t_minimap));
    if (!data->map || !data->minimap)
        return(printf("Error\n: malloc failed\n"), exit(1));
    i = ft_strlen(av[1]);
    if (ft_strncmp(av[1] + i - 4, ".cub", 5) != 0)
        return(ft_error("Error\n: file not valid\n"));
    data->map = read_map(av[1]);
    pars_the_color(data);
    pars_texture(data);
}

static void	print_controls(void)
{
	printf(YELLOW "\n");
    printf("\t\t███    ███  █████  ██████  ███████ ██████   █████      ██████  ██ ██ ██ ██ ██   ██\n");
    printf("\t\t████  ████ ██   ██ ██   ██      ██ ██   ██ ██   ██     ██   ██ ██ ██ ██ ██ ██  ██\n");
    printf("\t\t██ ████ ██ ███████ ██████      ██  ██████  ███████     ██████  ██ ██ ██ ██ █████\n");
    printf("\t\t██  ██  ██ ██   ██ ██   ██    ██   ██   ██ ██   ██     ██   ██ ██ ██ ██ ██ ██  ██\n");
    printf("\t\t██      ██ ██   ██ ██   ██    ██   ██████  ██   ██     ██████  ██ ██ ██ ██ ██   ██\n");
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


int main(int ac, char **av)
{
    t_data data;

    print_controls();
    check_argument(av, ac, &data);
    init_game(&data);
    game_loop(&data);
    mlx_loop(data.mlx);
    return 0;
}