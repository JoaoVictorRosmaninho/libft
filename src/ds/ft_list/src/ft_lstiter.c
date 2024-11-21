/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:16:08 by jv                #+#    #+#             */
/*   Updated: 2024/11/20 17:54:38 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
  t_node *node;

  node = lst->head;
	while (node != NULL)
	{
		f(node->data->content.p);
		node = node->next;
	}
}
