/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:12:01 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/04 22:03:18 by olaaroub         ###   ########.fr       */
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
    Ay:  Ay = Ay +  (Ax - x)  /  cos(O); // becose he has  a same ray len (same |PA| in above example);

    and if  we  want to calculat Ax we use the same method

*/


void vertical_intersection(t_data *data, t_vect *hit)
{
    t_vect ray_dir;
    double x, y;

    x = data->player.x;
    y = data->player.y;

    ray_dir.x = cos(data->start_angle);
    ray_dir.y = sin(data->start_angle);

    // if (fabs(ray_dir.x) < EPSILON)
    //     return;
    if (ray_dir.x < 0)
        hit->x = floor(x / SOF) * SOF - EPSILON;
    else
        hit->x = floor(x / SOF) * SOF + SOF;
    hit->y = y + ((hit->x - x) / ray_dir.x) * ray_dir.y;

}

double draw_vray(t_data *data , t_raycast_vars* vars)
{
    // t_vect hit;
    // t_vect step;

    vertical_intersection(data, &vars->hit);
    // if (fabs(cos(data->start_angle)) < EPSILON)
    //     return INT_MAX;
    if (cos(data->start_angle) > 0)
        vars->step.x = SOF;
    else
        vars->step.x = -SOF;
    vars->step.y = vars->step.x * tan(data->start_angle);
    while (vars->hit.x >= 0 && vars->hit.x < data->x_max * SOF &&
           vars->hit.y >= 0 && vars->hit.y < data->y_max * SOF)
    {
        vars->map.x = (int)vars->hit.x / SOF;
        vars->map.y = (int)vars->hit.y / SOF;
        if (vars->map.y >= 0 && vars->map.y < data->y_max &&
            vars->map.x >= 0 && vars->map.x < (int)ft_strlen(data->map->map[(int)vars->map.y]))
        {
            if (data->map->map[(int)vars->map.y][(int)vars->map.x] == '1' || ((data->map->map[(int)vars->map.y][(int)vars->map.x] == 'D' ||
                data->map->map[(int)vars->map.y][(int)vars->map.x] == 'O' || data->map->map[(int)vars->map.y][(int)vars->map.x] == 'F') && BONUS == 1))
                {
                    if(data->map->map[(int)vars->map.y][(int)vars->map.x] == 'D')
                        vars->hit_door_v = true;
                    else if(data->map->map[(int)vars->map.y][(int)vars->map.x] == 'O')
                        vars->hit_door_ov = true;
                    else if(data->map->map[(int)vars->map.y][(int)vars->map.x] == 'F')
                        vars->hit_fire_v = true;
                    break;
                }
        }
        else
            break;
        vars->hit.x += vars->step.x;
        vars->hit.y += vars->step.y;
    }
    vars->v_hit.x = vars->hit.x;
    vars->v_hit.y = vars->hit.y;
    return (sqrt(pow(vars->hit.x - data->player.x, 2) + pow(vars->hit.y - data->player.y, 2)));
}

void horizontal_intersection(t_data *data, t_vect *hit)
{
    double rayDirx;
    double rayDiry;
    double x;
    double y;

    x = data->player.x;
    y = data->player.y;
    rayDirx = cos(data->start_angle);
    rayDiry = sin(data->start_angle);

    // if (fabs(rayDiry) < EPSILON)
    //     return ;
    if (rayDiry < 0)
        hit->y = floor(y / SOF) * SOF - EPSILON;
    else
        hit->y = floor(y / SOF) * SOF + SOF;
    hit->x = x + ((hit->y - y) / rayDiry) * rayDirx;
}

double draw_hray(t_data *data, t_raycast_vars* vars)
{
    // t_vect hit;
    // t_vect step;
    // (void)hit_door_oh;

    horizontal_intersection(data, &vars->hit);
    if (sin(data->start_angle) > 0)
        vars->step.y = SOF;
    else
        vars->step.y = -SOF;
    vars->step.x = vars->step.y / tan(data->start_angle);
    while (vars->hit.x >= 0 && vars->hit.x < data->x_max * SOF &&
           vars->hit.y >= 0 && vars->hit.y < data->y_max * SOF)
    {
        vars->map.x = (int)(vars->hit.x / SOF);
        vars->map.y = (int)(vars->hit.y / SOF);
        // printf("%c\n", data->map->map[(int)map.y][(int)map.x]);
        if (vars->map.y >= 0 && vars->map.y < data->y_max &&
            vars->map.x >= 0 && vars->map.x < (int)ft_strlen(data->map->map[(int)vars->map.y]) &&
            (data->map->map[(int)vars->map.y][(int)vars->map.x] == '1' || ((data->map->map[(int)vars->map.y][(int)vars->map.x] == 'D' ||
             data->map->map[(int)vars->map.y][(int)vars->map.x] == 'O' || data->map->map[(int)vars->map.y][(int)vars->map.x] == 'F') && BONUS == 1)))
            {
                if(data->map->map[(int)vars->map.y][(int)vars->map.x] == 'D')
                    vars->hit_door_h = true;
                else if(data->map->map[(int)vars->map.y][(int)vars->map.x] == 'O')
                    vars->hit_door_oh = true;
                else if(data->map->map[(int)vars->map.y][(int)vars->map.x] == 'F')
                        vars->hit_fire_h = true;
                break;
            }
        vars->hit.x += vars->step.x;
        vars->hit.y += vars->step.y;
    }
    vars->h_hit.x = vars->hit.x;
    vars->h_hit.y = vars->hit.y;
    return (sqrt(pow(vars->hit.x - data->player.x, 2) + pow(vars->hit.y - data->player.y, 2)));
}

static void    hit_horizontal(t_data *data, t_raycast_vars *vars, double hlen)
{
    data->hit.x = vars->h_hit.x;
    data->hit.y = vars->h_hit.y;
    data->hit_door = vars->hit_door_h;
    data->hit_open_door = vars->hit_door_oh;
    data->hit_fire = vars->hit_fire_h;
    data->ray_dist = hlen;
    data->ray_dist *= cos(data->start_angle - data->angle);
    // data->projection_dist = (SCREEN_W / 2) / tan(FOV_ANGLE / 2);
    data->projection_dist = PROJECTION_DIST;
    data->wallhight = (SOF / data->ray_dist) * data->projection_dist;
    data->start_draw = (SCREEN_H / 2) - (data->wallhight / 2);
    data->end_draw = (SCREEN_H / 2) + (data->wallhight / 2);
    if (data->start_draw < 0)
        data->start_draw = 0;
    if (data->end_draw >= SCREEN_H)
        data->end_draw = SCREEN_H;
}

static void    hit_vertical(t_data *data, t_raycast_vars *vars, double vlen)
{
    data->hit.x = vars->v_hit.x;
    data->hit.y = vars->v_hit.y;
    data->is_vertical = true;
    data->hit_door = vars->hit_door_v;
    data->hit_open_door = vars->hit_door_ov;
    data->hit_fire = vars->hit_fire_v;
    data->ray_dist = vlen;
    data->ray_dist *= cos(data->start_angle - data->angle);
    // data->projection_dist = (SCREEN_W / 2) / tan(FOV_ANGLE / 2);
    data->projection_dist = PROJECTION_DIST;
    data->wallhight = (SOF / data->ray_dist) * data->projection_dist;
    data->start_draw = (SCREEN_H / 2) - (data->wallhight / 2);
    data->end_draw = (SCREEN_H / 2) + (data->wallhight / 2);
    if (data->start_draw < 0)
        data->start_draw = 0;
    if (data->end_draw >= SCREEN_H)
        data->end_draw = SCREEN_H;
}

double raycast(t_data *data)
{
    double hlen;
    double vlen;
	ft_memset(data->vars_v, 0, sizeof(t_raycast_vars));
	ft_memset(data->vars_h, 0, sizeof(t_raycast_vars));

    hlen = draw_hray(data, data->vars_h);
    vlen = draw_vray(data, data->vars_v);
    data->is_vertical = false;
    if (hlen < vlen)
        hit_horizontal(data, data->vars_h, hlen);
    else
        hit_vertical(data, data->vars_v, vlen);
    return 0;
}
