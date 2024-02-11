/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 23:38:53 by jv                #+#    #+#             */
/*   Updated: 2024/02/11 09:46:47 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../linked.h"

t_node	*ft_lstnew_node(void *data, DataType type)
{
	t_node	*node;

	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	if (type == STRING)
		node->data = mk_string_content((char *)data);
	else if (type == INTEGER)
		node->data = mk_int_content(*(int *)data);
	else if (type == DOUBLE)
		node->data = mk_double_content(*(double *)data);
	else if (type == CHAR)
		node->data = mk_char_content(*(char *)data);
	else if (type == FLOAT)
		node->data = mk_float_content(*(float *)data);
	else if (type == GENERIC)
		node->data = mk_generic_content(data);
	else if (type == DATA) 
		node->data = (Data *)data;
	node->next = NULL;
	return (node);
}
