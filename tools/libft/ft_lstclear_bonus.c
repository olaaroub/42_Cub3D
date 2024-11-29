/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:14:08 by ohammou-          #+#    #+#             */
/*   Updated: 2023/11/22 18:59:37 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;

	if (!del || !lst || !*lst)
		return ;
	while (*lst)
	{
		node = *lst;
		del((*lst)->content);
		(*lst) = (*lst)->next;
		free(node);
	}
}
