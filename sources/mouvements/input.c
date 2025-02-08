/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:16:40 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/07 23:02:13 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_key(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_error(data, "Au revoir", 0);
	return (0);
}

int	mouse_input(int x, int y, void *param)
{
	static int	old_x;
	int			distance;
	float		sense;
	float		rotation;
	t_data		*data;

	if (BONUS == 0)
		return (0);
	data = (t_data *)param;
	(void)y;
	sense = 0.02;
	distance = x - old_x;
	if (abs(distance) > 100)
	{
		old_x = x;
		return (0);
	}
	rotation = ROT_SPEED * sense * distance;
	data->angle += rotation;
	if (data->angle >= TWO_PI)
		data->angle -= TWO_PI;
	if (data->angle < 0)
		data->angle += TWO_PI;
	old_x = x;
	return (0);
}

int	key_press(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == XK_Escape)
		exit_key(data);
	else if (key == XK_f && BONUS == 1)
		open_door(data);
	else if (key == XK_e && BONUS == 1)
		close_door(data);
	else if (key == XK_d)
		data->moves.d_pressed = 1;
	else if (key == XK_a)
		data->moves.a_pressed = 1;
	else if (key == XK_w)
		data->moves.w_pressed = 1;
	else if (key == XK_s)
		data->moves.s_pressed = 1;
	else if (key == XK_Left)
		data->moves.turn_left = 1;
	else if (key == XK_Right)
		data->moves.turn_right = 1;
	return (0);
}

int	key_release(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == XK_d)
		data->moves.d_pressed = 0;
	else if (key == XK_a)
		data->moves.a_pressed = 0;
	else if (key == XK_w)
		data->moves.w_pressed = 0;
	else if (key == XK_s)
		data->moves.s_pressed = 0;
	else if (key == XK_Left)
		data->moves.turn_left = 0;
	else if (key == XK_Right)
		data->moves.turn_right = 0;
	return (0);
}
