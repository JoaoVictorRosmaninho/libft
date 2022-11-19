/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:13:35 by jv                #+#    #+#             */
/*   Updated: 2022/04/17 20:36:28 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lstclear(t_list *lst, void (*del)(void*))
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
		if (del)
      del(node->content);
    else 
      free(node->content);
		node = node->next;
		free(tmp);
	}
}
