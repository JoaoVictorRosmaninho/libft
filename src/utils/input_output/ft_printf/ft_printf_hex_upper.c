/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_upper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:42:10 by jv                #+#    #+#             */
/*   Updated: 2024/11/17 15:24:14 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

ssize_t	ft_printf_hex_upper(int n)
{
	ssize_t	len;
	char	number[128] = { 0 };

	len = 0;
	if (!n)
		len = ft_putstr_fd("0", 1);
	else
	{
		int2hex(n, 1, number);
		len += ft_putstr_fd(number, 1);
	}
	return (len);
}
