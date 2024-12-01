/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:24:12 by olaaroub          #+#    #+#             */
/*   Updated: 2024/12/01 00:28:42 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "ft_printf_fd.h"

void	ft_putptr_pr(int fd, unsigned long l, int *count)
{
	ft_putstr_pr(fd, "0x", count);
	if (l >= 16)
		ft_puthex(fd, l / 16, count);
	ft_putchar_pr(fd, "0123456789abcdef"[l % 16], count);
}
