/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:51:14 by jv                #+#    #+#             */
/*   Updated: 2022/06/26 00:04:58 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

ssize_t	ft_putstr_fd(char *s, int fd)
{
	if (!s && fd >= 0)
		return (write(fd, "(null)", 6));
	if (fd >= 0)
		return (write(fd, s, ft_strlen(s)));
	return (0);
}