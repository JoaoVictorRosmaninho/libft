/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:12:42 by jv                #+#    #+#             */
/*   Updated: 2024/03/10 14:59:55 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

void	ft_lstadd_front(t_list *lst, t_node *new)
{
	if (lst->head == NULL) 
  {
    lst->head = new;
    lst->tail = new;
  }
	else
	{
    lst->head->prev = new;
		new->next = lst->head;
		lst->head = new;
	}
  lst->size++;
}
