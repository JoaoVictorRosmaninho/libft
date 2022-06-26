/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:49:21 by jv                #+#    #+#             */
/*   Updated: 2022/06/26 00:10:49 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

ssize_t	ft_putnbr_fd(int n, int fd)
{
	char	*number;
	ssize_t	bytes_write;

	bytes_write = 0;
	number = ft_itoa(n);
	bytes_write += write(fd, number, ft_strlen(number));
	free(number);
	return (bytes_write);
}
