/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 23:49:52 by jv                #+#    #+#             */
/*   Updated: 2022/04/19 19:17:12 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char		*s;
	unsigned char			*d;

	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	if (dest > src)
	{
		while (n--)
			d[n] = s[n];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
