/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 03:26:08 by sosugimo          #+#    #+#             */
/*   Updated: 2021/01/05 00:42:47 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	static char *save;
	char		*buf = NULL;
	ssize_t		size;

	if (!(buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	if (save == NULL)
	{
		save = (char *)malloc(sizeof(char) * 1);
		save = "\0";
	}
	while (find_newline(save) == -1)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1)
			return (-1);
		buf[size] = '\0';
		save = ft_strjoin(save, buf);
		if (size == 0)
			break ;
	}
	free(buf);
	if (!(*line = (char *)malloc(sizeof(char) * ft_linelen(save) + 1)))
		return (-1);
	ft_strlcpy(*line, save, ft_linelen(save) + 1);
	save = save + ft_linelen(save) + 1;
	if (size == 0)
		return (0);
	return (1);
}

