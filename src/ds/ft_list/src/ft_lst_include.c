/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_include.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:55:14 by jv                #+#    #+#             */
/*   Updated: 2024/03/23 22:46:31 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

t_node* ft_lst_include(t_list *lst, void* item, uint8_t (*f)(void*, void*))
{
	t_node	*node;

	if (!lst || lst->size < 1)
		return (NULL);
  	node = lst->head;
	while (node != NULL)
	{
		if (f(item, node->data->content))
            return (node);
		node = node->next;
	}

	return (NULL);
}
