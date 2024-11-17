/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_lower.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:36:18 by jv                #+#    #+#             */
/*   Updated: 2024/11/16 23:43:52 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

ssize_t	ft_printf_hex_lower(int n)
{
	ssize_t	len;
	char	number[128];

	len = 0;
	if (!n)
		len = ft_putstr_fd("0", 1);
	else
	{
		int2hex(n, 0, number);
		len += ft_putstr_fd(number, 1);
	}
	return (len);
}
