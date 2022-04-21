/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:49:22 by jv                #+#    #+#             */
/*   Updated: 2022/04/21 14:10:40 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_calloc(size_t COUNT, size_t ELTSIZE)
{
	void	*ptr;

	ptr = malloc(COUNT * ELTSIZE);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, COUNT * ELTSIZE);
	return (ptr);
}
