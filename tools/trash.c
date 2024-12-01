/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:43:03 by olaaroub          #+#    #+#             */
/*   Updated: 2024/12/01 17:43:33 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    del(void *add)
{
    free(add);
}

void    free_trash(t_list **trash)
{
    ft_lstclear(trash, del);
}

void    add_to_trash(void *add, t_list **trash)
{
    t_list *new;

    new = ft_lstnew(add);
    ft_lstadd_back(trash, new);
}