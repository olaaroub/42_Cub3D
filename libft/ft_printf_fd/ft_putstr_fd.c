/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:24:17 by olaaroub          #+#    #+#             */
/*   Updated: 2024/12/01 00:28:52 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "ft_printf_fd.h"

void	ft_putstr_pr(int fd, char *str, int *count)
{
	if (!str)
		return (ft_putstr_pr(fd, "(null)", count));
	while (*str)
	{
		ft_putchar_pr(fd, *str, count);
		str++;
	}
}
