/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:48:59 by jv                #+#    #+#             */
/*   Updated: 2024/11/23 11:13:45 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_arena_alloc(size_t chunk, t_coliseu *coliseu)
{
	void	*memory;
	long	real_chunk;

	if (!coliseu || !chunk)
		return (NULL);
	real_chunk = ft_align(chunk);
	if (!coliseu->region)
	{
		if (!coliseu->size)
			return (NULL);
		ft_coliseu_create(coliseu);
		memory = ft_find_or_create_arena(coliseu, chunk);
	}
	else
	{
		memory = coliseu->region->begin;
		if ((real_chunk + sizeof(t_arena)) > PTRDIFF_MAX)
			return (NULL);
		if (coliseu->region->begin + real_chunk > coliseu->region->end)
			memory = ft_find_or_create_arena(coliseu, real_chunk);
	}
	coliseu->region->begin += real_chunk;
	return (memory);
}

// TODO create a coliseceu creator on arena memory 
t_coliseu* ft_coliseu_create_on_arena( size_t size, enum arena_type type ) {
	
	t_coliseu* coliseu = NULL;
	t_coliseu  temp    = { .door = NULL, .region = NULL, .type = type, .size = size };

	coliseu = ft_calloc(1, sizeof(t_coliseu), &temp);

	coliseu->door   = temp.region;
	coliseu->region = temp.region;
	coliseu->type   = type;
	coliseu->size   = temp.size - sizeof(t_coliseu);

	return coliseu;
}


t_arena	*ft_arena_init(size_t chunk)
{
	t_arena	*arena;

	if (chunk & (chunk -1))
		chunk = ft_arena_normalizer(chunk);
	if (chunk < sizeof(void *) || (chunk - sizeof(void *)) < ARENA_ALIGN_SIZE_IN_BYTES)
	{
		printf("tamanho %ld menor que o minimo aceitável\n", chunk);
		return (NULL);
	}

	if (chunk <= sizeof(t_arena)) 
		return (NULL);
	arena = (t_arena *) malloc(chunk);
	if (!arena)
	{
		printf("Tamanho, insuficiente para Arena\n");
		return (NULL);
	}
	
	arena->chunk = chunk;
	arena->begin = (char *) arena + sizeof(t_arena);
	arena->end   = (char *) arena + chunk;
	arena->next  = NULL;
	
	return (arena);
}

void	ft_coliseu_create(t_coliseu *coliseu)
{
	coliseu->door = ft_arena_init(coliseu->size);
	if (!coliseu->door)
		return ;
	coliseu->region       = coliseu->door;
	coliseu->total_arenas = 1;
}

void	*ft_find_or_create_arena(t_coliseu *coliseu, size_t chunk)
{
	t_ctx_arena	ctx;

	ctx.arena      = coliseu->region;
	ctx.arena_prev = NULL;
	while (ctx.arena && (long) chunk > (ctx.arena->end - ctx.arena->begin))
	{
		ctx.arena_prev = ctx.arena;
		ctx.arena      = ctx.arena->next;
	}
	if (ctx.arena) {
		coliseu->region = ctx.arena;
		return (ctx.arena->begin);
	}
	if (coliseu->region && coliseu->size)
		ctx.real_size = coliseu->region->chunk;
	else
		ctx.real_size = coliseu->size;
	while ((long)(chunk + sizeof(t_arena)) >= ctx.real_size)
		ctx.real_size <<= 1;
	 
	if (coliseu->type == ARENA_POOL || ctx.arena == NULL) {
		ctx.arena            = ft_arena_init(ctx.real_size);
		ctx.arena_prev->next = ctx.arena;
		coliseu->region      = ctx.arena;
		
		coliseu->total_arenas++;
	} else {
		ctx.arena->chunk = (ctx.arena->end - ctx.arena->begin) * 2;
		ctx.arena        = realloc(ctx.arena, ctx.arena->chunk);

		if (!ctx.arena) ft_printf("Error: realloc arena fail\n");
	}

	return (ctx.arena->begin);
}

t_coliseu	*ft_coliseu_manager(enum e_types action)
{
	static t_coliseu	coliseus[NUMBER_OF_COLISEUS] = {0};
	unsigned short int	index;
	t_coliseu			*ptr;

	index = 0;
	if (!coliseus[0].region)
		ft_coliseu_initialize(coliseus, ARENA_32KB, NUMBER_OF_COLISEUS);
	if (action == TAKE)
	{
		index = 1;
		ptr = &coliseus[0];
		while (index < NUMBER_OF_COLISEUS)
		{
			if ((coliseus[index].region->end - coliseus[index].region->begin)
				> (ptr->region->end - ptr->region->begin))
				ptr = &coliseus[index];
			index++;
		}
		return (ptr);
	}
	index = 0;
	while (index < NUMBER_OF_COLISEUS)
		ft_arena_destroy(&coliseus[index++]);
	return (NULL);
}
