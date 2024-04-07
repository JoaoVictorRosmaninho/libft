/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:13:35 by jv                #+#    #+#             */
/*   Updated: 2024/04/06 12:59:08 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list *lst)
{
	t_node	*node;

	if (!lst)
		return ;
	while ((node = ft_lstpop_head(lst)) != NULL)
	{
		ft_lstdelone(node);
	}
}
