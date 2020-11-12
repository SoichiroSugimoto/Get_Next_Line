/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 03:26:08 by sosugimo          #+#    #+#             */
/*   Updated: 2020/11/13 01:07:00 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	static char *save;
	char		*buf;
	ssize_t		size;

	*buf = NULL;
	while (find_newline(save) == -1)
	{
		size = read(fd, buf, 1);
		if (size == -1)
			return (-1);
		save = ft_strjoin(save, buf);
	}
	ft_strlcpy(*line, save, find_newline(save));
	save = save + find_newline(save) + 1;
	return (size);
}
