/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:13:35 by jv                #+#    #+#             */
/*   Updated: 2022/04/23 19:04:34 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static void	clear(t_list *node, void (*del)(void*))
{
	t_list	*tmp;

	if (del)
	{
		while (node != NULL)
		{
			tmp = node;
			del(node->content);
			node = node->next;
			free(tmp);
		}
	}
	else
	{
		while (node != NULL)
		{
			tmp = node;
			node = node->next;
			free(tmp);
		}
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (!lst)
		return ;
	clear(*lst, del);
	*lst = NULL;
}
