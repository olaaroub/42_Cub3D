/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 23:44:35 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/05 23:44:53 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_position_of_player_in_minimap(t_data *data, int x_draw, int y_draw)
{
	if (data->minimap->map_x == (int)data->player.x / SOF
		&& data->minimap->map_y == (int)data->player.y / SOF
		&& !data->minimap->flag)
	{
		data->minimap->player.x = ((x_draw + fabs(data->player.x / SOF
						- data->minimap->map_x)) * MI_SIZE) - 10;
		data->minimap->player.y = ((y_draw + fabs(data->player.y / SOF
						- data->minimap->map_y)) * MI_SIZE) - 10;
		data->minimap->flag = true;
	}
}