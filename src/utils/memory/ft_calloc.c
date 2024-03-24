/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:49:22 by jv                #+#    #+#             */
/*   Updated: 2024/03/24 15:37:02 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"
#include "../../../includes/arena.h"

void	*ft_calloc(size_t COUNT, size_t ELTSIZE, t_coliseu* coliseu)
{
	void	*ptr;

	if (!coliseu)
		coliseu = ft_coliseu_manager(TAKE);

	ptr = ft_arena_alloc(COUNT * ELTSIZE,  coliseu);
	
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, COUNT * ELTSIZE);
	return (ptr);
}
