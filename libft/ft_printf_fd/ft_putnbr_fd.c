/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:24:08 by olaaroub          #+#    #+#             */
/*   Updated: 2024/12/01 00:29:30 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

void	ft_putnbr(int fd, long nb, int *count)
{
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar_pr(fd, '-', count);
	}
	if (nb >= 10)
		ft_putnbr(fd, nb / 10, count);
	ft_putchar_pr(fd, nb % 10 + '0', count);
}
