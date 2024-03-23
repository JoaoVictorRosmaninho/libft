/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:00:18 by jv                #+#    #+#             */
/*   Updated: 2024/03/23 15:53:41 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

char	*ft_strdup(const char *str, t_coliseu* coliseu)
{
	size_t		size_buffer;
	char		*new_str;

	if (!str)
		return (NULL);
	size_buffer = ft_strlen(str) + 1;
	new_str = (char *) ft_calloc(1, size_buffer, coliseu);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, size_buffer);
	return (new_str);
}
