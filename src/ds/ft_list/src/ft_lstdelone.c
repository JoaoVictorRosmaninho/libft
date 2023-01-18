/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:15:32 by jv                #+#    #+#             */
/*   Updated: 2022/04/09 22:16:03 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../linked.h"

void	ft_lstdelone(t_node *node, void (*del)(void*))
{
	if (!node || !del)
		return ;
	del(node->data->content);
  free(node->data);
	free(node);
}
