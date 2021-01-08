/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 03:26:08 by sosugimo          #+#    #+#             */
/*   Updated: 2021/01/09 05:04:52 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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

int		free_save(char **save, char **buf)
{
	char *tmp;

	tmp = *save;
	if (!(*save = ft_strjoin(*save + ft_linelen(*save) + 1, "")))
	{
		all_free(buf, save);
		return (ERROR);
	}
	free(tmp);
	if (!**save)
		safe_free(save);
	return (SUCCESS);
}

int		get_next_line(int fd, char **line)
{
	static char *save;
	char		*buf;
	ssize_t		size;
	char 		*tmp;

	if (!line)
		return (-1);
	size = 1;
	if (!(buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	while ((find_newline(save) == -1) && (size > 0))
	{
		if ((size = read(fd, buf, BUFFER_SIZE)) == -1)
			return (all_free(&buf, &save));
		buf[size] = '\0';
		tmp = save;
		if (!(save = ft_strjoin(save, buf)))
			return (all_free(&buf, &save));
		free(tmp);
	}
	safe_free(&buf);
	if (!(*line = (char *)malloc(sizeof(char) * ft_linelen(save) + 1)))
		return (all_free(&buf, &save));
	if (*save)
	{
		ft_strlcpy(*line, save, ft_linelen(save));
		tmp = save;
		if (!(save = ft_strjoin(save + ft_linelen(save) + 1, "")))
			return (all_free(&buf, &save));
		free(tmp);
		if (!*save)
		{
			free(save);
			save = NULL;
		}
	}
	return (size == 0 ? 0 : 1);
}
