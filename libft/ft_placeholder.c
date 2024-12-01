/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_placeholder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:38:29 by olaaroub          #+#    #+#             */
/*   Updated: 2024/02/14 22:32:12 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_placeholder(char placeholder, va_list args)
{
	int	count;

	count = 0;
	if (placeholder == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (placeholder == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (placeholder == 'd' || placeholder == 'i')
		count += ft_putnbr_base(va_arg(args, int), 10, placeholder);
	else if (placeholder == 'x' || placeholder == 'X')
		count += ft_putnbr_base(va_arg(args, unsigned int), 16, placeholder);
	else if (placeholder == 'u')
		count += ft_putnbr_base(va_arg(args, unsigned int), 10, placeholder);
	else if (placeholder == '%')
		count += ft_putchar('%');
	else if (placeholder == 'p')
		count += ft_putptr(va_arg(args, void *), placeholder);
	else
		count += write(1, &placeholder, 1);
	return (count);
}
