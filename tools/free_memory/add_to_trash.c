/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_trash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:11:34 by ohammou-          #+#    #+#             */
/*   Updated: 2024/09/05 19:14:12 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void    add_to_trash(void *add, t_list **trash)
{
    t_list *new;

    new = ft_lstnew(add);
    ft_lstadd_back(trash, new);
}