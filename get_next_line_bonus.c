/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theoppon <theoppon@student.42belgium.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:24:59 by theoppon          #+#    #+#             */
/*   Updated: 2026/01/26 19:34:03 by theoppon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	update_saved(char **saved, char *rest)
{
	if (!rest || *rest == '\0')
	{
		free(rest);
		*saved = NULL;
	}
	else
		*saved = rest;
}

static char	*extract_line(char **saved)
{
	char	*line;
	char	*rest;
	size_t	i;

	if (!saved || !*saved)
		return (NULL);
	if (**saved == '\0')
		return (free(*saved), *saved = NULL, NULL);
	i = 0;
	while ((*saved)[i] && (*saved)[i] != '\n')
		i++;
	if ((*saved)[i] == '\n')
		i++;
	line = gnl_substr(*saved, 0, i);
	if (!line)
		return (free(*saved), *saved = NULL, NULL);
	rest = gnl_strdup(*saved + i);
	free(*saved);
	update_saved(saved, rest);
	return (line);
}

static char	*handle_read_result(char *saved, char *buffer)
{
	free(buffer);
	if (!saved)
		return (NULL);
	if (*saved == '\0')
		return (free(saved), NULL);
	return (saved);
}

static char	*read_and_save(int fd, char *saved)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(saved), NULL);
	bytes_read = 1;
	while (!gnl_strchr(saved, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(saved), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		saved = gnl_strjoin(saved, buffer);
		if (!saved)
			return (free(buffer), NULL);
	}
	return (handle_read_result(saved, buffer));
}

char	*get_next_line(int fd)
{
	static char	*saved[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	saved[fd] = read_and_save(fd, saved[fd]);
	if (!saved[fd])
		return (NULL);
	line = extract_line(&saved[fd]);
	return (line);
}
