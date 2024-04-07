/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:16:21 by jv                #+#    #+#             */
/*   Updated: 2024/04/06 12:59:08 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parser(char *token, va_list items, int fout)
{
	int	len;

	len = 0;
	if (*token == 'd' || *token == 'i')
		len = ft_putnbr_fd(va_arg(items, int), fout);
	else if (*token == 'c')
		len = ft_putchar_fd(va_arg(items, int), fout);
	else if (*token == '%')
		len = ft_putchar_fd('%', fout);
	else if (*token == 's')
		len = ft_putstr_fd(va_arg(items, char *), fout);
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
		len += ft_putchar_fd(*(--token), fout);
		len += ft_putchar_fd(*(++token), fout);
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
			len += parser((char *)(TEMPLATE + index + 1), arg_list, 1);
			index++;
		}
		else
			len += ft_putchar_fd(TEMPLATE[index], 1);
		index++;
	}
	va_end(arg_list);
	return (len);
}

int	ft_fprintf(int fout, const char *TEMPLATE, ...)
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
			len += parser((char *)(TEMPLATE + index + 1), arg_list, fout);
			index++;
		}
		else
			len += ft_putchar_fd(TEMPLATE[index], fout);
		index++;
	}
	va_end(arg_list);
	return (len);
}
