/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:43:03 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/04 23:31:49 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    del(void *addr)
{
    if(addr)
        free(addr);
}

void    free_trash(t_list **trash)
{
    // void *tmp;

    ft_lstclear(trash, del);
    // while( *trash)
    // {
    //     tmp = *trash;
    //     // free((*trash)->content);
    //     *trash = (*trash)->next;
    //     free(tmp);
    // }
}

void    add_to_trash(t_list **trash, void *addr)
{
    t_list *new;

    new = ft_lstnew(addr);
    ft_lstadd_back(trash, new);
}

static void bonus_cleanup(t_data *data)
{
    int i;

    if(data->animations->door_tex)
    {
        i = 0;
        while(i < DOOR_FRAMES && data->animations->door_tex[i] )
            mlx_destroy_image(data->mlx, data->animations->door_tex[i++]->texture);
    }
    if(data->animations->hand_tex )
    {
        i = 0;
        while(i < HAND_FRAMES && data->animations->hand_tex[i])
            mlx_destroy_image(data->mlx, data->animations->hand_tex[i++]->texture);
    }
    if(data->animations->fire_tex)
    {
        i = 0;
        while(i < FIRE_FRAMES && data->animations->fire_tex[i])
            mlx_destroy_image(data->mlx, data->animations->fire_tex[i++]->texture);
    }
}

void	ft_error(t_data* data,  char *str, int exit_code)
{
    free_trash(&data->trash);
    if(data->mlx != NULL)
    {

        if(data->north_tex)
            mlx_destroy_image(data->mlx, data->north_tex->texture);
        if(data->south_tex)
            mlx_destroy_image(data->mlx, data->south_tex->texture);
        if(data->west_tex)
            mlx_destroy_image(data->mlx, data->west_tex->texture);
        if(data->east_tex)
            mlx_destroy_image(data->mlx, data->east_tex->texture);
        if(BONUS)
            bonus_cleanup(data);
        if(data->img)
            mlx_destroy_image(data->mlx, data->img->img);
        mlx_destroy_window(data->mlx, data->mlx_win);
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    if(exit_code == 1)
	    write(2, str, ft_strlen(str));
    else
        printf("%s\n", str);
    exit(exit_code);
}

