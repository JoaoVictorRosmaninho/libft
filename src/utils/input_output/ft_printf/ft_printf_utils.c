/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:57:36 by jv                #+#    #+#             */
/*   Updated: 2024/03/23 15:59:37 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

void	reverse_array(char *str, int end)
{
	char	ch;
	int		ini;

	ini = 0;
	while (ini < end)
	{
		ch = str[ini];
		str[ini] = str[end];
		str[end] = ch;
		ini++;
		end--;
	}
}

char	*int2hex(unsigned int n, unsigned char op)
{
	unsigned char	index;
	char			number[128];
	char			ch;

	index = 0;
	ft_memset(number, 0, 128);
	while (n > 0)
	{
		ch = n % 16;
		if (ch > 9)
		{
			if (!op)
				number[index++] = 'a' + (ch - 10);
			else
				number[index++] = 'A' + (ch - 10);
		}
		else
			number[index++] = '0' + ch;
		n /= 16;
	}
	number[index] = '\0';
	reverse_array(number, index - 1);
	return (ft_strdup(number, NULL));
}

char	*lint2hex(unsigned long int n)
{
	unsigned char	index;
	char			number[128];
	char			ch;

	index = 0;
	ft_memset(number, 0, 128);
	while (n > 0)
	{
		ch = n % 16;
		if (ch > 9)
			number[index++] = 'a' + (ch - 10);
		else
			number[index++] = '0' + ch;
		n /= 16;
	}
	number[index] = '\0';
	reverse_array(number, index - 1);
	return (ft_strdup(number, NULL));
}
