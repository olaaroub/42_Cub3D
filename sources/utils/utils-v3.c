/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:14:33 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/29 02:04:51 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int cont_character(char *str, int c)
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