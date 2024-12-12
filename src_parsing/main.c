/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:51:29 by ohammou-          #+#    #+#             */
/*   Updated: 2024/12/10 23:10:30 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int    get_x(char **map)
{
    int j;
    size_t nb;

    j = 0;
    nb = 0;
    while (map[j])
    {
        if (ft_strlen(map[j]) >= nb)
            nb = ft_strlen(map[j]);
        j++;
    }
    return nb;
}

int main(int ac, char **av)
{
    if (ac < 2)
        return 1;
    check_option(av[1]);
    data_global()->map = read_map(av[1]);
    data_global()->y_max = ft_strlen_blm9lob(data_global()->map.map);
    data_global()->x_max = get_x(data_global()->map.map);
    main_of_drawing();
    mlx_loop(data_global()->mlx);

    return 0;
}