/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theoppon <theoppon@student.42belgium.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:47:33 by theoppon          #+#    #+#             */
/*   Updated: 2026/01/11 00:46:57 by theoppon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
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

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*t;
	char	*start_t;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		t = malloc(1);
		if (!t)
			return (NULL);
		*t = '\0';
		return (t);
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
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

char	*ft_strdup(const char *s)
{
	char	*t;
	char	*u;

	if (!s)
		return (NULL);
	t = malloc(ft_strlen(s) + 1);
	if (!t)
		return (NULL);
	u = t;
	while (*s)
		*t++ = *s++;
	*t = '\0';
	return (u);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined_string;
	char	*start;
	char	*temp;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	joined_string = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined_string)
		return (NULL);
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
