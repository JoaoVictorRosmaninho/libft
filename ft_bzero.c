/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:40:00 by jv                #+#    #+#             */
/*   Updated: 2022/04/09 21:40:57 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_bzero(void *BLOCK, size_t SIZE)
{
	size_t	index;

	if (!BLOCK)
		return ;
	index = 0;
	while (index < SIZE)
	{
		*(((unsigned char *) BLOCK) + index) = 0;
		index++;
	}
}
