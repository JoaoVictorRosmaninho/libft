/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_for_each.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:58:06 by jv                #+#    #+#             */
/*   Updated: 2024/11/20 17:53:52 by joao             ###   ########.fr       */
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
		f(node->data->content.p);
		node = node->next;
	}
}
