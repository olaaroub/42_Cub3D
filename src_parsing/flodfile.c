/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flodfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:33:24 by ohammou-          #+#    #+#             */
/*   Updated: 2025/01/19 16:03:52 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    check_floodfile(char **map)
{
    int i;
    int j;

    j = 0;
    while (map[j])
    {
        i = 0;
        while (map[j][i])
        {
            if (map[j][i] == 'F')
            {
                if (map[j][i + 1] == ' ' || (i - 1 >= 0 && map[j][i - 1] == ' '))
                    ft_error("mamsdodach\n");
                if (map[j + 1][i] == ' ' || (j - 1 >= 0 && map[j - 1][i] == ' '))
                    ft_error("masd9atch\n");
                if (map[j][i + 1] == '\0' || (i - 1 >= 0 && map[j][i - 1] == '\0'))
                    ft_error("mamsdodach2\n");
                if (map[j + 1][i] == '\0' || (j - 1 >= 0 && map[j - 1][i] == '\0'))
                    ft_error("masd9atch2\n");
            }
            i++;
        }
        j++;
    }
}

void    flodfile(char **map, int i, int j)
{
    int len;

    len = ft_strlen(map[j]);
    if (j < 0 || j >= ft_strlen_blm9lob(map) ||i < 0 || i >= len)
        return ;
    if (map[j][i] == '1' || map[j][i] == 'F' || map[j][i] == ' ')
        return ;
    map[j][i] = 'F';
    flodfile(map, i + 1,j);
    flodfile(map, i,j + 1);
    flodfile(map, i - 1,j);
    flodfile(map, i,j - 1);
}

// bool chack_ifIsValid(char **map, int i, int j)
// {
//     if (i > 0 && map[j][i - 1] == ' ')
//         return false;
//     else if (map[j][i] && (map[j][i + 1] == ' ' || !map[j][i + 1]))
//         return false;
//     else if (j > 0 && map[j - 1][i] == ' ')
//         return false;
//     else if (map[j] && (map[j + 1] == ' ' || !map[j][i])) 
// }

// bool check_mapifitSurrounded(char **map)
// {
//     int i;
//     int j;

//     j = 0;
//     while (map[j])
//     {
//         i = 0;
//         while (map[j][i])
//         {
//             if (map[i] == '0')
//             {
                
//             }
//             i++;
//         }
        
//         j++;
//     }
// }