/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 03:26:08 by sosugimo          #+#    #+#             */
/*   Updated: 2021/01/06 19:39:53 by sosugimo         ###   ########.fr       */
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

char	*free_save(char *save, char *buf)
{
	char *tmp;

	tmp = save;
	if (!(save = ft_strjoin(save + ft_linelen(save) + 1, "")))
	{
		all_free(&buf, &save);
		return (NULL);
	}
	free(tmp);
	if (!*save)
		safe_free(&save);
	return (save);
}

char	*str_n_join(char *save, char *buf)
{
	char *tmp;

	tmp = save;
	if (!(save = ft_strjoin(save, buf)))
	{
		all_free(&buf, &save);
		return (NULL);
	}
	free(tmp);
	return (save);
}

int		get_next_line(int fd, char **line)
{
	static char *save;
	char		*buf;
	ssize_t		size;

	size = 1;
	if (!(buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)) || !line)
		return (-1);
	while ((find_newline(save) == -1) && (size > 0))
	{
		if ((size = read(fd, buf, BUFFER_SIZE)) == -1)
			return (all_free(&buf, &save));
		buf[size] = '\0';
		if ((save = str_n_join(save, buf)) == NULL)
			return (-1);
	}
	safe_free(&buf);
	if (!(*line = (char *)malloc(sizeof(char) * ft_linelen(save) + 1)))
		return (all_free(&buf, &save));
	if (*save)
	{
		ft_strlcpy(*line, save, ft_linelen(save));
		if ((save = free_save(save, buf)) == NULL)
			return (-1);
	}
	return (size == 0 ? 0 : 1);
}
