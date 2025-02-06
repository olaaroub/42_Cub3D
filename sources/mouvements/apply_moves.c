/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:19:25 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/06 18:44:00 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*int	protect_value(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}*/

void	turn(t_data *data)
{
	if (data->moves.turn_left)
	{
		data->angle -= ROT_SPEED;
		if (data->angle < 0)
			data->angle += TOW_PI;
	}
	if (data->moves.turn_right)
	{
		data->angle += ROT_SPEED;
		if (data->angle >= TOW_PI)
			data->angle -= TOW_PI;
	}
}

static void	update_door_animation(t_data *data)
{
	static int	door_counter;
	int			frame_step;

	if (data->moves.opened == true)
		frame_step = 1;
	else
		frame_step = -1;
	if (door_counter % DOOR_FRAME_STEP == 0)
	{
		data->anim->d_curr = data->anim->d_curr + frame_step;
		if (data->anim->d_curr < 0)
			data->anim->d_curr = 0;
		if (data->anim->d_curr >= DOOR_FRAMES)
			data->anim->d_curr = DOOR_FRAMES - 1;
	}
	door_counter++;
	if (door_counter >= 100)
		door_counter = 0;
	if (door_counter <= 0)
		door_counter = 0;
}

int	apply_moves(void *parm)
{
	t_data				*data;

	static unsigned int (anim_counter), (fire_counter);
	data = (t_data *)parm;
	if (data->moves.d_pressed)
		move_right(data);
	if (data->moves.a_pressed)
		move_left(data);
	if (data->moves.w_pressed)
		move_up(data);
	if (data->moves.s_pressed)
		move_down(data);
	if (data->moves.turn_left || data->moves.turn_right)
		turn(data);
	update_door_animation(data);
	if (++anim_counter % ANIM_STEP == 0)
		data->anim->h_curr = (data->anim->h_curr + 1) % HAND_FRAMES;
	if (anim_counter >= UINT_MAX - 1000)
		anim_counter = 0;
	if (++fire_counter % FIRE_FRAME_STEP == 0)
		data->anim->f_curr = (data->anim->f_curr + 1) % FIRE_FRAMES;
	if (fire_counter >= UINT_MAX - 1000)
		fire_counter = 0;
	render(data);
	return (0);
}
