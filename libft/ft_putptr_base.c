/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:24:36 by olaaroub          #+#    #+#             */
/*   Updated: 2024/02/15 11:21:11 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_base(unsigned long n, int base, char c)
{
	int			count;
	const char	*hexa;

	hexa = "0123456789abcdef";
	count = 0;
	if (n < (unsigned long)base)
		return (ft_putchar(hexa[n]));
	else
	{
		count += ft_putptr_base(n / base, base, c);
		return (count + ft_putptr_base(n % base, base, c));
	}
	return (count);
}
