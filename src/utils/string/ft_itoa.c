/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:03:49 by jv                #+#    #+#             */
/*   Updated: 2024/03/23 18:02:36 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

static void	ft_rev(char *s1, int size)
{
	int		ini;
	char	aux;

	ini = 0;
	while (ini < size)
	{
		aux = s1[ini];
		s1[ini] = s1[size];
		s1[size] = aux;
		ini++;
		size--;
	}
}

static void	convert(int nb, char *number, int index)
{
	if (nb >= 0)
	{
		while (nb > 0)
		{
			number[index++] = '0' + (nb % 10);
			nb /= 10;
		}
		if (index == 0)
			number[index++] = '0';
		number[index] = '\0';
	}
	else
	{
		number[index++] = '0' + ((nb % -10) * -1);
		nb /= -10;
		while (nb > 0)
		{
			number[index++] = '0' + (nb % 10);
			nb /= 10;
		}
		number[index++] = '-';
		number[index] = '\0';
	}
}

char	*ft_itoa(int n, t_coliseu* coliseu)
{
	char	*number;

	number = ft_calloc(12, sizeof(char), coliseu);
	if (!number)
		return (NULL);
	convert(n, number, 0);
	ft_rev(number, ft_strlen(number) - 1);
	return (number);
}
