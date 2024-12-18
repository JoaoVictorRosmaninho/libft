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

#include "../../includes/libft.h"

void	ft_arena_free(t_coliseu *coliseu)
{
	t_arena	*arena;

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

void	ft_arena_destroy(t_coliseu *coliseu)
{
	t_arena	*arena;
	t_arena	*_arena;

	arena = coliseu->door;
	while (arena)
	{
		_arena = arena;
		arena = arena->next;
		free(_arena);
	}
}

size_t ft_coliseu_occuped_size(t_coliseu* coliseu) {
	return coliseu->region->begin - (char*)coliseu->region - sizeof(t_arena) ;
}

size_t ft_coliseu_avalible_size(t_coliseu* coliseu) {
	return coliseu->region->end - coliseu->region->begin;
}


void	ft_coliseu_initialize(t_coliseu	*group,
	size_t size_of_coliseu, size_t length)
{
	size_t	index;

	index = 0;
	while (index < length)
	{
		group[index].region = NULL;
		group[index].door = NULL;
		group[index].size = size_of_coliseu;
		group[index].total_arenas = 0;
		ft_coliseu_create(&group[index]);
		index++;
	}
}


t_coliseu ft_coliseu_realloc_block(t_coliseu* coliseu) {


	//coliseu->region = realloc(coliseu->region, coliseu->size * 2);

	t_coliseu new  =  { .size = coliseu->size * 2 , .type = coliseu->type, .door = NULL, .region = NULL };

	ft_coliseu_create(&new);

	ft_memcpy(new.region->begin, (unsigned char*)coliseu->region  + sizeof(t_arena), ft_coliseu_occuped_size(coliseu));

	new.region->avaliable -= ft_coliseu_occuped_size(coliseu);
	new.region->begin     += ft_coliseu_occuped_size(coliseu);

	ft_arena_destroy(coliseu);

	return new;
}