/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:48:36 by jv                #+#    #+#             */
/*   Updated: 2022/06/26 00:02:14 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

ssize_t	ft_putendl_fd(char *s, int fd)
{
	ssize_t	bytes_write;

	bytes_write = 0;
	bytes_write += write(fd, s, ft_strlen(s));
	bytes_write += write(fd, "\n", 1);
	return (bytes_write);
}
