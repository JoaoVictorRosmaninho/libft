/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:49:44 by jv                #+#    #+#             */
/*   Updated: 2022/11/02 11:56:56 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

ssize_t	ft_printf_uint(unsigned int num)
{
	unsigned char	index;
	char			number[16];

	index = 0;
	if (!num)
		number[index++] = '0';
	else
	{
		while (num > 0)
		{
			number[index++] = '0' + (num % 10);
			num /= 10;
		}
	}
	number[index] = '\0';
	reverse_array(number, index - 1);
	return (ft_putstr_fd(number, 1));
}
