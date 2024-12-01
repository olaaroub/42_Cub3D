/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:32:17 by olaaroub          #+#    #+#             */
/*   Updated: 2024/02/14 22:32:23 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *placeholder, ...)
{
	va_list	args;
	int		count;

	va_start(args, placeholder);
	count = 0;
	while (*placeholder != '\0')
	{
		if (*placeholder == '%' && *(placeholder + 1))
			count += ft_placeholder(*(++placeholder), args);
		else if (*placeholder != '%')
			count += write(1, placeholder, 1);
		++placeholder;
	}
	va_end(args);
	return (count);
}
