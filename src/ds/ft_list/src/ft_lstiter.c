/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:16:08 by jv                #+#    #+#             */
/*   Updated: 2024/03/10 14:59:55 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

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
