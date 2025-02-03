/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:12:01 by ohammou-          #+#    #+#             */
/*   Updated: 2025/02/03 02:00:02 by olaaroub         ###   ########.fr       */
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

double draw_vray(t_data *data , t_vect map, t_vect *v_hit, bool *hit_door, bool *hit_door_ov, bool *hit_fire)
{
    t_vect hit;
    t_vect step;

    vertical_intersection(data, &hit);
    // if (fabs(cos(data->start_angle)) < EPSILON)
    //     return INT_MAX;
    if (cos(data->start_angle) > 0)
        step.x = SOF;
    else
        step.x = -SOF;
    step.y = step.x * tan(data->start_angle);
    while (hit.x >= 0 && hit.x < data->x_max * SOF &&
           hit.y >= 0 && hit.y < data->y_max * SOF)
    {
        map.x = (int)hit.x / SOF;
        map.y = (int)hit.y / SOF;
        if (map.y >= 0 && map.y < data->y_max &&
            map.x >= 0 && map.x < (int)ft_strlen(data->map->map[(int)map.y]))
        {
            if (data->map->map[(int)map.y][(int)map.x] == '1' || ((data->map->map[(int)map.y][(int)map.x] == 'D' ||
                data->map->map[(int)map.y][(int)map.x] == 'O' || data->map->map[(int)map.y][(int)map.x] == 'F') && BONUS == 1))
                {
                    if(data->map->map[(int)map.y][(int)map.x] == 'D')
                        *hit_door = true;
                    else if(data->map->map[(int)map.y][(int)map.x] == 'O')
                        *hit_door_ov = true;
                    else if(data->map->map[(int)map.y][(int)map.x] == 'F')
                        *hit_fire = true;
                    break;
                }
        }
        else
            break;
        hit.x += step.x;
        hit.y += step.y;
    }
    v_hit->x = hit.x;
    v_hit->y = hit.y;
    return (sqrt(pow(hit.x - data->player.x, 2) + pow(hit.y - data->player.y, 2)));
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

double draw_hray(t_data *data, t_vect map, t_vect *h_hit, bool *hit_door, bool *hit_door_oh, bool *hit_fire)
{
    t_vect hit;
    t_vect step;
    // (void)hit_door_oh;

    horizontal_intersection(data, &hit);
    // if (fabs(sin(data->start_angle)) < EPSILON)
    //     return INT_MAX;
    if (sin(data->start_angle) > 0)
        step.y = SOF;
    else
        step.y = -SOF;
    step.x = step.y / tan(data->start_angle);
    while (hit.x >= 0 && hit.x < data->x_max * SOF &&
           hit.y >= 0 && hit.y < data->y_max * SOF)
    {
        map.x = (int)(hit.x / SOF);
        map.y = (int)(hit.y / SOF);
        // printf("%c\n", data->map->map[(int)map.y][(int)map.x]);
        if (map.y >= 0 && map.y < data->y_max &&
            map.x >= 0 && map.x < (int)ft_strlen(data->map->map[(int)map.y]) &&
            (data->map->map[(int)map.y][(int)map.x] == '1' || ((data->map->map[(int)map.y][(int)map.x] == 'D' ||
             data->map->map[(int)map.y][(int)map.x] == 'O' || data->map->map[(int)map.y][(int)map.x] == 'F') && BONUS == 1)))
            {
                if(data->map->map[(int)map.y][(int)map.x] == 'D')
                    *hit_door = true;
                else if(data->map->map[(int)map.y][(int)map.x] == 'O')
                    *hit_door_oh = true;
                else if(data->map->map[(int)map.y][(int)map.x] == 'F')
                        *hit_fire = true;
                break;
            }
        hit.x += step.x;
        hit.y += step.y;
    }
    h_hit->x = hit.x;
    h_hit->y = hit.y;
    return (sqrt(pow(hit.x - data->player.x, 2) + pow(hit.y - data->player.y, 2)));
}

double raycast(t_data *data)
{
    double hlen;
    double vlen;
    t_vect h_hit;
    t_vect v_hit;
    t_vect map;
    bool hit_door_h = false;
    bool hit_door_v = false;
    bool hit_door_oh = false;
    bool hit_door_ov = false;
    bool hit_fire_h = false;
    bool hit_fire_v = false;

    map.x = 0;
    map.y = 0;
    hlen = draw_hray(data, map, &h_hit, &hit_door_h, &hit_door_oh, &hit_fire_h);
    vlen = draw_vray(data, map, &v_hit, &hit_door_v, &hit_door_ov , &hit_fire_v);
    data->is_vertical = false;
    if (hlen < vlen)
    {
        data->hit.x = h_hit.x;
        data->hit.y = h_hit.y;
        data->hit_door = hit_door_h;
        data->hit_open_door = hit_door_oh;
        data->hit_fire = hit_fire_h;
        return hlen;
    }
    else
    {
        data->hit.x = v_hit.x;
        data->hit.y = v_hit.y;
        data->is_vertical = true;
        data->hit_door = hit_door_v;
        data->hit_open_door = hit_door_ov;
        data->hit_fire = hit_fire_v;
        return vlen;
    }
    return 0;
}
