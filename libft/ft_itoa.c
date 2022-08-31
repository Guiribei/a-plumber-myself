/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:18:50 by guribeir          #+#    #+#             */
/*   Updated: 2022/04/28 15:20:15 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*ptr;
	int				len;
	int				sign;
	unsigned int	nbr;

	nbr = n;
	sign = 0;
	len = ft_numlen(n);
	if (n < 0 && ++len && ++sign)
		nbr = (unsigned int)n * -1;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	if (n == 0)
		ptr[0] = '0';
	ptr[len] = '\0';
	while (len)
	{
		ptr[(--len)] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	if (sign == 1)
		ptr[0] = '-';
	return (ptr);
}
