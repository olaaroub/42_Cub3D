/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:24:00 by olaaroub          #+#    #+#             */
/*   Updated: 2024/12/01 00:29:34 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

void	ft_puthex(int fd, unsigned long l, int *count)
{
	if (l >= 16)
		ft_puthex(fd, l / 16, count);
	ft_putchar_pr(fd, "0123456789abcdef"[l % 16], count);
}
