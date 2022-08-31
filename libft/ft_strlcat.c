/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:19:37 by guribeir          #+#    #+#             */
/*   Updated: 2022/04/28 15:42:03 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	s_len;
	size_t	d_len;

	s_len = 0;
	while (src[s_len])
		s_len++;
	d_len = 0;
	while (dst[d_len])
		d_len++;
	if (size == 0)
		return (s_len);
	i = 0;
	while ((src[i] != 0) && (d_len + i) < (size -1))
	{
		dst[d_len + i] = src[i];
		i++;
	}
	if (i < size)
		dst[d_len + i] = '\0';
	if (d_len > size)
		return (s_len + size);
	return (d_len + s_len);
}
