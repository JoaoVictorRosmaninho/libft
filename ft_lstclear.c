/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:13:35 by jv                #+#    #+#             */
/*   Updated: 2022/04/09 22:15:23 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;
	t_list	*tmp;

	if (!lst)
		return ;
	node = *lst;
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
          while (node != NULL)
          {
		tmp = node;
		node = node->next;
		free(tmp);
          }
	*lst = NULL;
}
