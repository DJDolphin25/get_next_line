/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theoppon <theoppon@student.42belgium.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:52:36 by theoppon          #+#    #+#             */
/*   Updated: 2026/01/11 02:24:19 by theoppon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **saved)
{
	char	*line;
	char	*rest;
	size_t	i;

	i = 0;
	while ((*saved)[i] && (*saved)[i] != '\n')
		i++;
	if ((*saved)[i] == '\n')
		i++;
	line = ft_substr(*saved, 0, i);
	if (!line)
		return (NULL);
	rest = ft_strdup(*saved + i);
	free(*saved);
	*saved = rest;
	if (*saved && **saved == '\0')
	{
		free(*saved);
		*saved = NULL;
	}
	return (line);
}

static char	*read_and_save(int fd, char *saved)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (saved);
	bytes_read = 1;
	while (bytes_read > 0 && (!saved || !ft_strchr(saved, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(saved);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		saved = ft_strjoin(saved, buffer);
	}
	free(buffer);
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved = read_and_save(fd, saved);
	if (!saved)
		return (NULL);
	if (!*saved)
	{
		free(saved);
		saved = NULL;
		return (NULL);
	}
	return (extract_line(&saved));
}
