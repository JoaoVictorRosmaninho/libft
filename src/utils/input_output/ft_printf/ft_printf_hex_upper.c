/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_upper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:42:10 by jv                #+#    #+#             */
/*   Updated: 2022/11/02 11:56:45 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

ssize_t	ft_printf_hex_upper(int n)
{
	ssize_t	len;
	char	*number;

	len = 0;
	if (!n)
		len = ft_putstr_fd("0", 1);
	else
	{
		number = int2hex(n, 1);
		len += ft_putstr_fd(number, 1);
		free(number);
	}
	return (len);
}
