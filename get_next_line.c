/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosugimo <sosugimo@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 03:26:08 by sosugimo          #+#    #+#             */
/*   Updated: 2021/02/22 02:50:38 by sosugimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		safe_free(char **st)
{
	free(*st);
	*st = NULL;
	return (0);
}

int		all_free(char **buf, char **save)
{
	safe_free(buf);
	safe_free(save);
	return (-1);
}

int		free_save(char **save, char *buf)
{
	char *tmp;

	tmp = *save;
	if (!(*save = ft_strjoin(*save + ft_linelen(*save) +
	(find_newline(*save) == -1 ? 0 : 1), "")))
	{
		all_free(&buf, save);
		return (ERROR);
	}
	free(tmp);
	if (!**save)
		safe_free(save);
	return (SUCCESS);
}

char	*str_n_join(char **save, char **buf)
{
	char *tmp;

	tmp = *save;
	if (!(*save = ft_strjoin(*save, *buf)))
	{
		all_free(buf, save);
		return (NULL);
	}
	free(tmp);
	return (*save);
}

int		get_next_line(int fd, char **line)
{
	static char *save;
	char		*buf;
	ssize_t		size;

	size = 1;
	if (!line || BUFFER_SIZE <= 0 || fd < 0)
		return (ERROR);
	if (!line || !(buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	while ((find_newline(save) == -1) && (size > 0))
	{
		if ((size = read(fd, buf, BUFFER_SIZE)) == -1)
			return (all_free(&buf, &save));
		buf[size] = '\0';
		if ((save = str_n_join(&save, &buf)) == NULL)
			return (-1);
	}
	safe_free(&buf);
	if (!(*line = (char *)malloc(sizeof(char) * ft_linelen(save) + 1)))
		return (all_free(&buf, &save));
	if (*save)
	{
		ft_strlcpy(*line, save, ft_linelen(save));
		if ((free_save(&save, buf)) == ERROR)
			return (-1);
	}
	return (size == 0 ? safe_free(&save) : 1);
}
