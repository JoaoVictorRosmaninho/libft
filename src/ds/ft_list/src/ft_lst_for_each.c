/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_for_each.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:58:06 by jv                #+#    #+#             */
/*   Updated: 2024/03/23 18:52:18 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

void ft_lst_for_each(t_list *lst, void (*f)(void *))
{
	t_node	*node;

	if (!lst)
		return ;
  	node = lst->head;
	while (node != NULL)
	{
		f(node->data->content);
		node = node->next;
	}
}
