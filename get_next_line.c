/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 03:26:08 by sosugimo          #+#    #+#             */
/*   Updated: 2021/01/05 01:50:40 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	safe_free(char **st)
{
	free(*st);
	*st = NULL;
}

int		all_free(char **buf, char **save)
{
	safe_free(buf);
	safe_free(save);
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	static char *save;
	char		*buf;
	ssize_t		size;
	char		*tmp;

	size = 1;
	if (!(buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	while ((find_newline(save) == -1) && (size > 0))
	{
		if ((size = read(fd, buf, BUFFER_SIZE)) == -1)
			return (all_free(&buf, &save));
		buf[size] = '\0';
		save = ft_strjoin(save, buf);
	}
	safe_free(&buf);
	if (!(*line = (char *)malloc(sizeof(char) * ft_linelen(save) + 1)))
		return (all_free(&buf, &save));
	ft_strlcpy(*line, save, ft_linelen(save) + 1);
	tmp = save;
	save = save + ft_linelen(save) + 1;
	return (size == 0 ? 0 : 1);
}
