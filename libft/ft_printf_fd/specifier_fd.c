/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:24:25 by olaaroub          #+#    #+#             */
/*   Updated: 2024/12/01 00:29:05 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "ft_printf_fd.h"

void	specifier(int fd, char spf, va_list args, int *count)
{
	if (spf == 's')
		ft_putstr_pr(fd, va_arg(args, char *), count);
	else if (spf == 'c')
		ft_putchar_pr(fd, va_arg(args, int), count);
	else if (spf == 'd')
		ft_putnbr(fd, va_arg(args, int), count);
	else if (spf == 'i')
		ft_putnbr(fd, va_arg(args, int), count);
	else if (spf == 'u')
		ft_unsigned(fd, va_arg(args, unsigned int), count);
	else if (spf == 'x')
		ft_puthex(fd, va_arg(args, unsigned int), count);
	else if (spf == 'X')
		ft_putchex(fd, va_arg(args, unsigned int), count);
	else if (spf == 'p')
		ft_putptr_pr(fd, va_arg(args, unsigned long), count);
	else
		ft_putchar_pr(fd, spf, count);
}
