/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:23:32 by olaaroub          #+#    #+#             */
/*   Updated: 2025/01/22 02:16:49 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf_fd.h"

int	ft_printf_fd(int fd, char const *str, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			specifier(fd, *(str + 1), args, &count);
			str++;
		}
		else if (*str != '%')
			ft_putchar_pr(fd, *str, &count);
		str++;
	}
	va_end(args);
	return (count);
}
