/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:32:59 by ohammou-          #+#    #+#             */
/*   Updated: 2024/12/01 02:40:11 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	main_of_drawing()
{
	open_the_window();
	get_postion(data_global(), data_global()->map.map);
	data_global()->i = data_global()->x;
	data_global()->j = data_global()->y;

	data_global()->x = (data_global()->x * 60) + 20;
	data_global()->y = (data_global()->y * 60) + 20;
	drawing();
	mlx_key_hook(data_global()->mlx_win, esc, NULL);
	mlx_hook(data_global()->mlx_win, 17, 0,krwa, NULL);
	mlx_hook(data_global()->mlx_win, 2, 1L<<0, move, NULL);
	mlx_loop_hook(data_global()->mlx, drawing, NULL);
}
