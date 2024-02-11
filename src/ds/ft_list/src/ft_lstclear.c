/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:13:35 by jv                #+#    #+#             */
/*   Updated: 2024/02/11 14:11:30 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../linked.h"

void	ft_lstclear(t_list *lst)
{
	t_node	*node;
	t_node	*tmp;

  tmp = NULL;
	if (!lst)
		return ;
	node = lst->head;
	while (node != NULL)
	{
		tmp = node;
		if (node->data->ffree)
      		node->data->ffree(node->data->content);
    	else 
    	{
    	  free(node->data->content);
    	}
		node = node->next;
    	free(tmp->data);
		free(tmp);
	}
}
