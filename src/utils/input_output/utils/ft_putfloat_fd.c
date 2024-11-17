/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:49:21 by jv                #+#    #+#             */
/*   Updated: 2024/11/03 21:12:09 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

ssize_t	ft_pufloat_fd(float n, int fd)
{
    t_coliseu	local = { 
        .door   = NULL, 
        .region = NULL, 
        .size   = ARENA_64B 
    };

	char    *number      = ft_itoa(n, &local);
	
    ssize_t  bytes_write = write(fd, number, ft_strlen(number));
	
    ft_arena_destroy(&local);
	
    return (bytes_write);
}
