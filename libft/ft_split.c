/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 21:47:35 by guribeir          #+#    #+#             */
/*   Updated: 2022/04/28 15:33:37 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_parts(char const *s, char c)
{
	size_t	parts;

	parts = 0;
	while (*s)
	{
		if (*s != c)
		{
			parts++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (parts);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	len;
	char	**ptr;

	if (!s)
		return (0);
	ptr = malloc((ft_count_parts(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (0);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			ptr[i++] = ft_substr(s - len, 0, len);
		}
		else
			s++;
	}
	ptr[i] = 0;
	return (ptr);
}
