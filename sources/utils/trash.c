/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:43:03 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/04 17:34:28 by olaaroub         ###   ########.fr       */
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