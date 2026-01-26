/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theoppon <theoppon@student.42belgium.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:47:33 by theoppon          #+#    #+#             */
/*   Updated: 2026/01/26 19:36:08 by theoppon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*gnl_substr(const char *s, unsigned int start, size_t len)
{
	char	*t;
	char	*start_t;

	if (!s)
		return (NULL);
	if (start >= gnl_strlen(s))
	{
		t = malloc(1);
		if (!t)
			return (NULL);
		*t = '\0';
		return (t);
	}
	if (gnl_strlen(s + start) < len)
		len = gnl_strlen(s + start);
	t = malloc(len + 1);
	if (!t)
		return (NULL);
	start_t = t;
	s += start;
	while (*s && len--)
		*t++ = *s++;
	*t = '\0';
	return (start_t);
}

char	*gnl_strdup(const char *s)
{
	char	*t;
	char	*u;

	if (!s)
		return (NULL);
	t = malloc(gnl_strlen(s) + 1);
	if (!t)
		return (NULL);
	u = t;
	while (*s)
		*t++ = *s++;
	*t = '\0';
	return (u);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*joined_string;
	char	*start;
	char	*temp;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (gnl_strdup(s2));
	joined_string = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!joined_string)
	{
		free(s1);
		return (NULL);
	}
	start = joined_string;
	temp = s1;
	while (*temp)
		*joined_string++ = *temp++;
	while (*s2)
		*joined_string++ = *s2++;
	*joined_string = '\0';
	free(s1);
	return (start);
}
