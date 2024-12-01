/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchex_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:23:56 by olaaroub          #+#    #+#             */
/*   Updated: 2024/12/01 00:29:38 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "ft_printf_fd.h"

void	ft_putchex(int fd, unsigned int l, int *count)
{
	if (l >= 16)
		ft_putchex(fd, l / 16, count);
	ft_putchar_pr(fd, "0123456789ABCDEF"[l % 16], count);
}
