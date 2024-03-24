/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:49:21 by jv                #+#    #+#             */
/*   Updated: 2024/03/23 18:03:57 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

ssize_t	ft_putnbr_fd(int n, int fd)
{
	char		*number;
	ssize_t		bytes_write;
	t_coliseu	local = { .door = NULL, .region = NULL, .size = ARENA_64B };

	bytes_write = 0;
	number = ft_itoa(n, &local);
	bytes_write += write(fd, number, ft_strlen(number));
	ft_arena_destroy(&local);
	return (bytes_write);
}
