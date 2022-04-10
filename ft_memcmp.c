/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 23:42:20 by jv                #+#    #+#             */
/*   Updated: 2022/04/09 23:46:52 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_memcmp(const void *A1, const void *A2, size_t SIZE)
{
	unsigned char		*a1;
	unsigned char		*a2;
	size_t				index;

	if (!A1 || !A2)
		return (0);
	index = 0;
	a1 = (unsigned char *) A1;
	a2 = (unsigned char *) A2;
	while (index < SIZE)
	{
		if (a1[index] != a2[index])
		{
			if (a1[index] < a2[index])
				return (-1);
			return ((int)(a2 - a1));
		}
		index++;
	}
	return (0);
}
