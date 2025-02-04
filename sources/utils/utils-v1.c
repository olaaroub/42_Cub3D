/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:36:09 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/04 17:37:03 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixelput(t_img *img, int x, int y, int color)
{
	char	*tmp;

	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	tmp = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)tmp = color;
}



bool is_valid_number(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (!ft_isdigit(str[i]))
            return false;
        i++;
    }
    return true;
}

int count_chars(char *str, int c)
{
    int cont;
    int i;

    cont = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            cont++;
        i++;
    }
    return (cont);
}

void    add_double_ptr_to_trash(t_data *data, void **add)
{
    int i = 0;
    while(add[i])
    {
        add_to_trash(&data->trash, add[i]);
        i++;
    }
    add_to_trash(&data->trash, add);
}


void	ft_error(t_data* data,  char *str)
{
    free_trash(&data->trash);
	write(1, str, ft_strlen(str));
	exit(1);
}

