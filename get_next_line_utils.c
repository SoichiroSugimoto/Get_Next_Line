/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:58:15 by sosugimo          #+#    #+#             */
/*   Updated: 2021/01/05 22:26:49 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //コメント

size_t	ft_strlen(const char *s)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

size_t	ft_linelen(const char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!(p = (char *)malloc(sizeof(char) *
		(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = '\0';
	return (p);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	//printf("L-HipHop\n");
	size_t i;

	i = 0;
	if (!src || !dst)
		return (0);
	if (!dstsize)
		return (ft_strlen(src));
	//printf("%s", src);
	while ((i != dstsize) && src[i])
	{
		//printf("dekiteru\n");
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	//printf("%s\n", dst);
	return (ft_strlen(src));
}

int		find_newline(char *st)
{
	int i;

	i = 0;
	if (!st)
		return (-1);
	while (st[i])
	{
		if (st[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
