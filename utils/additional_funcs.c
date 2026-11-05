/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 18:24:42 by juskola-          #+#    #+#             */
/*   Updated: 2026/11/05 23:50:00 by juskola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	count;
	int	nb;

	count = 1;
	nb = 0;
	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\r') || (str[i] == '\v') || (str[i] == '\f'))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			count *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb * count);
}

// This function creates a newly allocated copy of a string.
//
// The 's1' pointer references the null-terminated string to be
// duplicated.
char	*ft_strdup(const char *s1)
{
	char	*copy;

	copy = malloc(ft_strlen(s1) + 1);
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, s1, (size_t)ft_strlen(s1) + 1);
	return (copy);
}

// This function creates a newly allocated string containing the
// concatenation of two strings.
//
// The 's1' and 's2' pointers reference the null-terminated strings
// to concatenate.
char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	int		newlen;
	char	*new;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	newlen = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	new = malloc(newlen);
	if (!new)
		return (NULL);
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = '\0';
	return (new);
}

// This function copies a string into a destination buffer while
// ensuring that the resulting string is null-terminated, provided
// the buffer size is greater than zero.
//
// The 'dest' pointer references the destination buffer. The 'src'
// pointer references the source string to copy. The 'size'
// parameter specifies the size of the destination buffer.
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

// This function calculates the length of a null-terminated string.
//
// The 'str' pointer references the string whose length is
// calculated.
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
