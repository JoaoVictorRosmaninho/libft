/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:16:08 by jv                #+#    #+#             */
/*   Updated: 2022/04/09 22:16:54 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../linked.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
  t_node *node;

  node = lst->head;
	while (node != NULL)
	{
		f(node->data->content);
		node = node->next;
	}
}
