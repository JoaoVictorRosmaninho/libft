/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-paul <jde-paul@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:20:04 by jde-paul                #+#    #+#             */
/*   Updated: 2024/03/17 19:43:59 by jde-paul               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arena_free(void* buffer)
{
	t_coliseu* coliseu;
	t_arena*   arena;

	coliseu =  (t_coliseu*) buffer;
	if (!coliseu || !coliseu->door)
		return ;
	arena = coliseu->door;
	while (arena)
	{
		arena->begin = (char *) arena + sizeof(t_arena);
		arena = arena->next;
	}
	coliseu->region = coliseu->door;
}

void	ft_coliseu_rollback(t_arena *region, size_t rollback)
{
	if (!region)
		return ;
	if ((region->begin - rollback)
		< (region->end + sizeof(void*) - region->chunk))
		return ;
	region->begin -= rollback;
}

void	ft_arena_destroy(void*  buffer)
{
	t_coliseu* coliseu;
	t_arena*   arena;
	t_arena*   _arena;

	coliseu = (t_coliseu*) buffer;
	arena = coliseu->door;
	while (arena)
	{
		_arena = arena;
		arena = arena->next;
		free(_arena);
	}
	coliseu->door = NULL;
	coliseu->region = NULL;
}

void	ft_coliseu_initialize(t_coliseu	*group, size_t length, ...)
{
	size_t	index;
	va_list	ap;

	va_start(ap,  length);
	index = 0;
	while (index < length)
	{
		group[index].region = NULL;
		group[index].door = NULL;
		group[index].size = va_arg(ap, size_t);
		ft_coliseu_create(&group[index]);
		index++;
	}
}

void	ft_coliseu_release_all(void	*group, size_t length)
{
	size_t	   index = 0;
	t_coliseu* cs 	 = (t_coliseu*) group;

	while (index < length)
	{
		ft_arena_destroy(cs + index);
		index++;
	}
}
