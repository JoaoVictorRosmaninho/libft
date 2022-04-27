/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:49:22 by jv                #+#    #+#             */
/*   Updated: 2022/04/26 22:05:51 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_calloc(size_t COUNT, size_t ELTSIZE)
{
	void	*ptr;

	if (!COUNT || !ELTSIZE)
		return (NULL);
	if (COUNT == __SIZE_MAX__ || ELTSIZE == __SIZE_MAX__)
		return (NULL);
	ptr = malloc(COUNT * ELTSIZE);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, COUNT * ELTSIZE);
	return (ptr);
}
