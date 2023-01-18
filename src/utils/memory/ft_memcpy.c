/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 23:47:31 by jv                #+#    #+#             */
/*   Updated: 2022/04/19 19:15:21 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	*ft_memcpy(void *TO, const void *FROM, size_t size)
{
	size_t	index;

	if (!TO && !FROM)
		return (NULL);
	index = 0;
	while (index < size)
	{
		*(((unsigned char *) TO) + index) = *(((unsigned char *) FROM) + index);
		index++;
	}
	return (TO);
}
