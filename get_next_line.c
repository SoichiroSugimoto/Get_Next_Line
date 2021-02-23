/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 03:26:08 by sosugimo          #+#    #+#             */
/*   Updated: 2021/02/23 18:34:30 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		all_free(char **buf, char **save, int i)
{
	if (i == 1)
	{
		free(*buf);
		*buf = NULL;
		return (0);
	}
	else
	{
		free(*buf);
		*buf = NULL;
		free(*save);
		*save = NULL;
		return (-1);
	}
}

int		free_save(char **save, char *buf)
{
	char *tmp;

	tmp = *save;
	if (!(*save = ft_strjoin(*save + ft_linelen(*save) +
	(find_newline(*save) == -1 ? 0 : 1), "")))
	{
		all_free(&buf, save, 2);
		return (ERROR);
	}
	free(tmp);
	if (!**save)
		all_free(save, &buf, 2);
	return (SUCCESS);
}

char	*str_n_join(char **save, char **buf)
{
	char *tmp;

	tmp = *save;
	if (!(*save = ft_strjoin(*save, *buf)))
	{
		all_free(buf, save, 2);
		all_free(&tmp, save, 1);
		return (NULL);
	}
	all_free(&tmp, save, 1);
	return (*save);
}

int		cpy_line(char **save, char ***line, char **buf)
{
	if (**save)
	{
		ft_strlcpy(**line, *save, ft_linelen(*save));
		if ((free_save(save, *buf)) == ERROR)
			return (ERROR);
	}
	else if (ft_linelen(*save) == 0)
		***line = '\0';
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char *save;
	char		*buf;
	ssize_t		size;

	size = 1;
	if (!line || BUFFER_SIZE <= 0 || fd < 0 ||
		!(buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (ERROR);
	while ((find_newline(save) == -1) && (size > 0))
	{
		if ((size = read(fd, buf, BUFFER_SIZE)) == -1)
			return (all_free(&buf, &save, 2));
		buf[size] = '\0';
		if ((save = str_n_join(&save, &buf)) == NULL)
			return (ERROR);
	}
	all_free(&buf, &save, 1);
	if (!(*line = (char *)malloc(sizeof(char) * ft_linelen(save) + 1)))
		return (all_free(&buf, &save, 2));
	if ((cpy_line(&save, &line, &buf)) == ERROR)
		return (ERROR);
	return (size == 0 ? all_free(&save, &buf, 1) : 1);
}
