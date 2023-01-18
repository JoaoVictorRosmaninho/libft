/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:16:21 by jv                #+#    #+#             */
/*   Updated: 2022/06/25 23:24:15 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

static int	parser(char *token, va_list items)
{
	int	len;

	len = 0;
	if (*token == 'd' || *token == 'i')
		len = ft_putnbr_fd(va_arg(items, int), 1);
	else if (*token == 'c')
		len = ft_putchar_fd(va_arg(items, int), 1);
	else if (*token == '%')
		len = ft_putchar_fd('%', 1);
	else if (*token == 's')
		len = ft_putstr_fd(va_arg(items, char *), 1);
	else if (*token == 'x')
		len = ft_printf_hex_lower(va_arg(items, int));
	else if (*token == 'X')
		len = ft_printf_hex_upper(va_arg(items, int));
	else if (*token == 'u')
		len = ft_printf_uint(va_arg(items, unsigned int));
	else if (*token == 'p')
		len = ft_printf_ptr(va_arg(items, unsigned long int));
	else
	{
		len += ft_putchar_fd(*(--token), 1);
		len += ft_putchar_fd(*(++token), 1);
	}
	return (len);
}

int	ft_printf(const char *TEMPLATE, ...)
{
	size_t	index;
	va_list	arg_list;
	int		len;

	if (!TEMPLATE)
		return (0);
	va_start(arg_list, TEMPLATE);
	index = 0;
	len = 0;
	while (TEMPLATE[index])
	{
		if (TEMPLATE[index] == '%')
		{
			len += parser((char *)(TEMPLATE + index + 1), arg_list);
			index++;
		}
		else
			len += ft_putchar_fd(TEMPLATE[index], 1);
		index++;
	}
	va_end(arg_list);
	return (len);
}
