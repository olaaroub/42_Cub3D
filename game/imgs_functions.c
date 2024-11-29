/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgs_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:14:32 by ohammou-          #+#    #+#             */
/*   Updated: 2024/10/10 20:29:17 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void get_data_addr(t_img *img)
{
	img->img = mlx_new_image(data_global()->mlx,  data_global()->x_max * 60,  data_global()->y_max * 60);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);	
}

void put_and_destroy_img(t_img *img)
{
	mlx_put_image_to_window(data_global()->mlx, data_global()->mlx_win, img->img, 0, 0);
	mlx_destroy_image(data_global()->mlx, img->img);	
}