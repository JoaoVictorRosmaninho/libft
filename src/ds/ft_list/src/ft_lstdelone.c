/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:15:32 by jv                #+#    #+#             */
/*   Updated: 2024/02/11 10:09:02 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../linked.h"

void	ft_lstdelone(t_node *node)
{
	if (!node || !node->data->ffree )
		return ;
	node->data->ffree(node->data->content);
  	free(node->data);
	free(node);
}
