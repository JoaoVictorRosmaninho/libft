/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:58:06 by jv                #+#    #+#             */
/*   Updated: 2024/11/21 20:42:09 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *, t_coliseu*), t_coliseu* coliseu)
{
	t_list	*new_list;
	t_node	*node;
  	t_node  *new_node;

	if (!lst)
		return (NULL);
	new_list = (t_list *) ft_calloc(1, sizeof(t_list), coliseu);
 	node = lst->head;
	while (node != NULL)
	{
    	new_node = ft_lstnew_node(f(node->data->content.p, coliseu), node->data->content_type, coliseu);
		ft_lstadd_back(new_list, new_node);
		if (!new_node)
		{
			ft_lstclear(new_list);
			return (NULL);
		}
		node = node->next;
	}
	return (new_list);
}
