/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:11:47 by jv                #+#    #+#             */
/*   Updated: 2024/04/06 12:59:08 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list *lst, t_node *new)
{

	if (lst->tail == NULL)
    lst->head = lst->tail = new;
	else
	{
    new->prev = lst->tail;
    lst->tail->next = new; 
    lst->tail = new;
	}
  lst->size++;
}
