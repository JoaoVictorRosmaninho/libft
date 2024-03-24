/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:04:06 by jv                #+#    #+#             */
/*   Updated: 2024/03/23 23:26:11 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../../includes/libft.h"

void ft_lst_remove_node(t_list* lst, t_node* node)
{
	t_node	*prev;

    prev = node->prev;

    if (prev) {
        prev->next = node->next;
    } else {
        lst->head = node->next;
        if (lst->head)
            lst->head->prev = NULL;
    }
    node->prev = NULL;
    node->next = NULL;
    lst->size--;
}
