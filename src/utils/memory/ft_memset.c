/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:46:02 by jv                #+#    #+#             */
/*   Updated: 2022/04/10 14:47:09 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	*ft_memset(void *BLOCK, int C, size_t SIZE)
{
	unsigned char		value;
	size_t				index;

	value = (unsigned char) C;
	index = 0;
	while (index < SIZE)
	{
		*(((unsigned char *) BLOCK) + index) = value;
		index++;
	}
	return (BLOCK);
}
