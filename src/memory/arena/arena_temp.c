/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_temp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:06:40 by jv                #+#    #+#             */
/*   Updated: 2024/04/07 14:03:37 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

TmpArena    tmp_coliseu_new(t_coliseu* coliseu) {
    return (TmpArena) {
        .coliseu     =  coliseu,
        .prev_region =  coliseu->region,
        .prev_offset =  coliseu->region->begin,
        .has_next    =  coliseu->region->next != NULL ? 1 : 0
    };
}

void    tmp_coliseu_end(TmpArena*  tmp) {
    tmp->coliseu->region = tmp->prev_region;
    tmp->coliseu->region->begin = tmp->prev_offset;
    
    if (tmp->has_next == 0 && tmp->coliseu->region->next != NULL)
        ft_arena_destroy(tmp->coliseu->region->next);
}