/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:12:01 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/06 17:09:02 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*

	the prove to how I fined the first Intersection :
	ok, I have a  ray that  going in point P to A;

	y
	|___ A
	|  /|
	| / |
	|/__|________> x
		P

	- we have a equation is : cos(O) = Ax / |PA|  and sin(O) =  Ay /  |PA|;
	so: Ax  = |PA|.cos(O) and Ay = |PA|.sin(O);
	ok,  using this equation we try to  find  a equation that  find first point;
	we have a: Ax = x + ray.distance.cos(O) and Ay = y + ray.distance.sin(O);
	Ax: ray.distance = (Ax - x) /  cos(O);
	Ay:  Ay = Ay +  (Ax - x)  /  cos(O);
		// becose he has  a same ray len (same |PA| in above example);

	and if  we  want to calculat Ax we use the same method

*/

static double	draw_vray(t_data *data, t_raycast_vars *vars)
{
	vertical_intersection(data, &vars->hit);
	if (cos(data->start_angle) > 0)
		vars->step.x = SOF;
	else
		vars->step.x = -SOF;
	vars->step.y = vars->step.x * tan(data->start_angle);
	while (vars->hit.x >= 0 && vars->hit.x < data->x_max * SOF
		&& vars->hit.y >= 0 && vars->hit.y < data->y_max * SOF)
	{
		vars->map.x = (int)vars->hit.x / SOF;
		vars->map.y = (int)vars->hit.y / SOF;
		if (hit_tile_v(data, vars) == 69)
			break ;
		else if (hit_tile_v(data, vars) == 0)
			break ;
		vars->hit.x += vars->step.x;
		vars->hit.y += vars->step.y;
	}
	vars->v_hit.x = vars->hit.x;
	vars->v_hit.y = vars->hit.y;
	return (sqrt(pow(vars->hit.x - data->player.x, 2) + pow(vars->hit.y
				- data->player.y, 2)));
}

static double	draw_hray(t_data *data, t_raycast_vars *vars)
{
	horizontal_intersection(data, &vars->hit);
	if (sin(data->start_angle) > 0)
		vars->step.y = SOF;
	else
		vars->step.y = -SOF;
	vars->step.x = vars->step.y / tan(data->start_angle);
	while (vars->hit.x >= 0 && vars->hit.x < data->x_max * SOF
		&& vars->hit.y >= 0 && vars->hit.y < data->y_max * SOF)
	{
		vars->map.x = (int)(vars->hit.x / SOF);
		vars->map.y = (int)(vars->hit.y / SOF);
		if (hit_tile_h(data, vars) == 69)
			break ;
		vars->hit.x += vars->step.x;
		vars->hit.y += vars->step.y;
	}
	vars->h_hit.x = vars->hit.x;
	vars->h_hit.y = vars->hit.y;
	return (sqrt(pow(vars->hit.x - data->player.x, 2) + pow(vars->hit.y
				- data->player.y, 2)));
}

static void	hit_horizontal(t_data *data, t_raycast_vars *vars, double hlen)
{
	data->hit.x = vars->h_hit.x;
	data->hit.y = vars->h_hit.y;
	data->hit_door = vars->hit_door_h;
	data->hit_open_door = vars->hit_door_oh;
	data->hit_fire = vars->hit_fire_h;
	data->ray_dist = hlen;
	data->ray_dist *= cos(data->start_angle - data->angle);
	data->wallhight = (SOF / data->ray_dist) * data->projection_dist;
	data->start_draw = (SCREEN_H / 2) - (data->wallhight / 2);
	data->end_draw = (SCREEN_H / 2) + (data->wallhight / 2);
	if (data->start_draw < 0)
		data->start_draw = 0;
	if (data->end_draw > SCREEN_H)
		data->end_draw = SCREEN_H;
}

static void	hit_vertical(t_data *data, t_raycast_vars *vars, double vlen)
{
	data->hit.x = vars->v_hit.x;
	data->hit.y = vars->v_hit.y;
	data->is_vertical = true;
	data->hit_door = vars->hit_door_v;
	data->hit_open_door = vars->hit_door_ov;
	data->hit_fire = vars->hit_fire_v;
	data->ray_dist = vlen;
	data->ray_dist *= cos(data->start_angle - data->angle);
	data->wallhight = (SOF / data->ray_dist) * data->projection_dist;
	data->start_draw = (SCREEN_H / 2) - (data->wallhight / 2);
	data->end_draw = (SCREEN_H / 2) + (data->wallhight / 2);
	if (data->start_draw < 0)
		data->start_draw = 0;
	if (data->end_draw > SCREEN_H)
		data->end_draw = SCREEN_H;
}

double	raycast(t_data *data)
{
	double	hlen;
	double	vlen;

	ft_memset(data->vars_v, 0, sizeof(t_raycast_vars));
	ft_memset(data->vars_h, 0, sizeof(t_raycast_vars));
	hlen = draw_hray(data, data->vars_h);
	vlen = draw_vray(data, data->vars_v);
	data->is_vertical = false;
	if (hlen < vlen)
		hit_horizontal(data, data->vars_h, hlen);
	else
		hit_vertical(data, data->vars_v, vlen);
	return (0);
}
