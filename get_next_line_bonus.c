/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghoyuelo <ghoyuelo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:53:00 by ghoyuelo          #+#    #+#             */
/*   Updated: 2021/12/29 18:14:55 by ghoyuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char	*next_line(char *s)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	next = (char *)malloc((sizeof(char) * ft_strlen(s) - i + 1));
	if (!next)
		return (NULL);
	i++;
	j = 0;
	while (s[i])
		next[j++] = s[i++];
	next[j] = '\0';
	free(s);
	return (next);
}

char	*get_line(char *s)
{
	size_t	i;
	size_t	len;
	char	*line;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] != '\n' && s[i])
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	len = line_len(s, '\n');
	while (s[i] && i < len + 1)
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_s(int fd, char *s)
{
	char	*buffer;
	int		rd;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	rd = 1;
	while (!ft_strchr(s, '\n') && rd > 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[rd] = '\0';
		s = ft_strjoin(s, buffer);
	}
	free(buffer);
	return (s);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*s[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	s[fd] = read_s(fd, s[fd]);
	if (!s[fd])
		return (NULL);
	line = get_line(s[fd]);
	s[fd] = next_line(s[fd]);
	return (line);
}
