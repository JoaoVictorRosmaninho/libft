/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:49:22 by jv                #+#    #+#             */
/*   Updated: 2022/04/24 14:55:50 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_negative(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

static int	is_zero(int n)
{	
	if (n == 0)
		return (1);
	return (0);
}

static int	len_number(int n)
{
	int				len;
	unsigned int	l;

	len = 0;
	l = n;
	if (is_negative(l))
	{
		l = l * -1;
		len++;
	}
	while (l > 0)
	{
		l = l / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*num;
	int				len;
	unsigned int	nbr;

	nbr = n;
	len = len_number(n);
	if (is_zero(n))
		len++;
	if (is_negative(n))
		nbr = (unsigned int)n * -1;
	num = (char *)malloc(len + 1);
	if (!num)
		return (0);
	num[len--] = '\0';
	while (len >= 0 && nbr > 0)
	{
		num[len] = (nbr % 10) + '0';
		nbr = nbr / 10;
		len--;
	}
	if (is_zero(n))
		num[len] = '0';
	if (is_negative(n))
		num[len] = '-';
	return (num);
}
