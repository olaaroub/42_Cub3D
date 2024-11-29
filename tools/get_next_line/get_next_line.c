/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:05:17 by ohammou-          #+#    #+#             */
/*   Updated: 2024/08/26 01:13:54 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*before_new_line(char *bfr)
{
	int		i;
	char	*str;

	i = 0;
	if (!bfr)
		return ("");
	while (bfr[i++] != '\n' && bfr[i])
		;
	str = malloc(i + 1);
	ft_strlcpy(str, bfr, i + 1);
	free(bfr);
	return (str);
}

char	*after_new_line(char *bfr)
{
	char	*str;

	if (!bfr)
		return ("");
	while (*bfr != '\n' && *bfr != '\0')
		bfr++;
	if (*bfr == '\n')
	{
		str = malloc(ft_strlen(bfr + 1) + 1);
		ft_strlcpy(str, bfr + 1, ft_strlen(bfr) + 1);
		return (str);
	}
	return (NULL);
}

void	ft_bzero(char *s, size_t n)
{
	while (n--)
		s[n] = '\0';
}

char	*get_rest(char *bfrcopy, int fd, char *bfr, ssize_t len)
{
	static char	*remaining;

	while (!ft_sstrchr(bfrcopy, '\n'))
	{
		len = read(fd, bfr, BUFFER_SIZE);
		if (len < 0)
		{
			free(remaining);
			remaining = NULL;
			return (free(bfr), NULL);
		}
		bfr[len] = '\0';
		bfrcopy = ft_strjjoin(bfrcopy, remaining, bfr);
		ft_bzero(bfr, BUFFER_SIZE);
		free(remaining);
		remaining = NULL;
		if (len == 0)
			break ;
	}
	remaining = after_new_line(bfrcopy);
	if (len == 0 && bfrcopy[0] == '\0')
		return (free(bfrcopy), free(bfr), NULL);
	bfrcopy = before_new_line(bfrcopy);
	free(bfr);
	return (bfrcopy);
}

char	*get_next_line(int fd)
{
	char	*bfr;
	char	*bfrcopy;
	ssize_t	len;

	bfrcopy = "";
	len = 0;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	bfr = malloc(BUFFER_SIZE + 1);
	if (!bfr)
		return (NULL);
	bfrcopy = get_rest(bfrcopy, fd, bfr, len);
	return (bfrcopy);
}

//  int main(void)
//  {
//       int fd = open("file.txt", O_RDONLY);
//       for(int i = 0;i < 6;i++)
//       {
//           char *str = get_next_line(fd);
//           printf("%s",str);
//          //get_next_line(fd);
//        // printf(" i == %d\n", i);
//         free(str);
//        }
//         //   get_next_line(fd);
//         //   get_next_line(fd);
//         // get_next_line(fd);
//        // printf("%s",get_next_line(fd));

//     // char *s = get_next_line(fd);
//     //    printf("%s",s);
//     //    free(s);
//       //printf("%s",s);
//      // free(s);
//     //system("leaks a.out");

//        //get_next_line(fd);
//      // get_next_line(fd);
//     //  after_new_line("anas jawad\nhhh");
//   //printf("%s",ft_strjoin("hello","hi","bro"));
//   //printf("%s",before_new_line("anas jawad\nhhh"));

//  }
