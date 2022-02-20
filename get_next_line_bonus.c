/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 20:25:07 by ahamdy            #+#    #+#             */
/*   Updated: 2021/11/22 16:01:02 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include "get_next_line_bonus.h"
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

static void	_freemem(char **ptr)
{
	free(*ptr);
	*ptr = 0;
}

char	*line_manip(char **save)
{
	char	*tmp;
	char	*line;
	int		index;

	index = 0;
	while ((*save)[index] != '\n' && (*save)[index])
		index++;
	if ((*save)[index] == '\n')
	{
		line = ft_substr(*save, 0, index + 1);
		tmp = *save;
		*save = ft_strjoin(&(*save)[index + 1], "");
		_freemem(&tmp);
	}
	else
	{
		line = ft_strjoin(*save, "");
		_freemem(save);
	}
	if (*line == '\0')
		_freemem(&line);
	return (line);
}

char	*ft_read(int fd, char **save, char **read_buf)
{
	ssize_t	eof;
	char	*tmp;

	eof = 1;
	while (eof && !ft_strchr(*save, '\n'))
	{
		eof = read(fd, *read_buf, BUFFER_SIZE);
		(*read_buf)[eof] = 0;
		tmp = *save;
		*save = ft_strjoin(*save, *read_buf);
		_freemem(&tmp);
	}
	_freemem(read_buf);
	return (line_manip(save));
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*read_buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	read_buf = malloc(BUFFER_SIZE + 1);
	if (!read_buf)
		return (0);
	if (read(fd, read_buf, 0) < 0)
	{
		_freemem(&read_buf);
		return (NULL);
	}
	if (!save[fd])
		save[fd] = ft_strjoin("", "");
	return (ft_read(fd, &save[fd], &read_buf));
}
