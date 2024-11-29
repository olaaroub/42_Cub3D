/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:05:14 by ohammou-          #+#    #+#             */
/*   Updated: 2024/08/26 01:09:54 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (((char *)str)[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	if (!n && !dst)
		return (ft_strlen(src));
	i = ft_strlen(dst);
	j = 0;
	if (n <= i)
		return (ft_strlen(src) + n);
	while (j + i < n - 1 && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + ft_strlen(src));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(src);
	i = 0;
	if (!dstsize)
		return (j);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}

char	*ft_strjjoin(char *s1, char *s2, char *s3)
{
	char	*b;

	if (!s1)
		return (NULL);
	if (!s2)
		s2 = "";
	if (!s3)
		s3 = "";
	b = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!b)
		return (NULL);
	ft_strlcpy(b, s1, ft_strlen(s1) + 1);
	ft_strlcat(b, s2, ft_strlen(s2) + ft_strlen(s1) + 1);
	ft_strlcat(b, s3, ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (s1[0] != '\0')
		free(s1);
	return (b);
}

int	ft_sstrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}
