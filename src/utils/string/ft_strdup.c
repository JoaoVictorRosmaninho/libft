/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:00:18 by jv                #+#    #+#             */
/*   Updated: 2022/04/21 14:50:46 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

char	*ft_strdup(const char *str)
{
	size_t		size_buffer;
	char		*new_str;

	size_buffer = ft_strlen(str) + 1;
	new_str = (char *) malloc(size_buffer);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, size_buffer);
	return (new_str);
}
