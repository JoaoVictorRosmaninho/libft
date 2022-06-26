/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:47:09 by jv                #+#    #+#             */
/*   Updated: 2022/06/25 23:47:30 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

ssize_t	ft_printf_ptr(unsigned long int n)
{
	ssize_t	len;
	char	*number;

	len = 0;
	if (!n)
	{
		ft_putstr_fd("(nil)", 1);
		len = 5;
	}
	else
	{
		len += ft_putstr_fd("0x", 1);
		number = lint2hex(n);
		len += ft_putstr_fd(number, 1);
		free(number);
	}
	return (len);
}
