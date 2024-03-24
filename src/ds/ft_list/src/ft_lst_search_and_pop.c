/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_search_and_pop.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:55:14 by jv                #+#    #+#             */
/*   Updated: 2024/03/24 00:20:05 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

uint8_t ft_lst_search_and_pop(t_list *lst, void* item, uint8_t (*f)(void*, void*))
{
	t_node	*node;

	if (!lst || lst->size < 1)
		return(0);
	node = ft_lst_include(lst, item, f);
	if (node) {
		ft_lst_remove_node(lst, node);
		return (1);
	}
	return (0);
}
