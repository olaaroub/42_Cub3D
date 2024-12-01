/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:23:37 by olaaroub          #+#    #+#             */
/*   Updated: 2024/12/01 00:29:48 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>

int		ft_printf_fd(int fd, char const	*str, ...);

void	specifier(int fd, char spf, va_list args, int *count);
void	ft_unsigned(int fd, unsigned int nb, int *count);
void	ft_putchex(int fd, unsigned int l, int *count);
void	ft_puthex(int fd, unsigned long l, int *count);
void	ft_putptr_pr(int fd, unsigned long l, int *count);
void	ft_putstr_pr(int fd, char *str, int *count);
void	ft_putchar_pr(int fd, char ch, int *count);
void	ft_putnbr(int fd, long nb, int *count);

#endif