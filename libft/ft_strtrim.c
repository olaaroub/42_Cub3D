/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 22:59:28 by olaaroub          #+#    #+#             */
/*   Updated: 2023/11/22 21:21:54 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	char	*buff;
	size_t	i;
	size_t	j;

	i = 0;
	if (s1 && set)
	{
		j = ft_strlen(s1);
		if (j == 0)
			return (ft_strdup(""));
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && j > i && ft_strchr(set, s1[j - 1]))
			j--;
		ptr = malloc(j - i + 1);
		if (!ptr)
			return (NULL);
		buff = ptr;
		ft_strlcpy(buff, s1 + i, j - i + 1);
		return (ptr);
	}
	return (NULL);
}
