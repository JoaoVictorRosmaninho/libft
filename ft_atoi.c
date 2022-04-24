/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:38:41 by jv                #+#    #+#             */
/*   Updated: 2022/04/09 21:39:47 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_atoi(const char *STRING)
{
	int	i;
	int	sign;
	int	n;

	if (!STRING)
		return (0);
	i = 0;
	sign = 1;
	n = 0;
	while (ft_isspace(STRING[i]) && STRING[i])
		i++;
	if (STRING[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (STRING[i] == '+')
		i++;
	while ((STRING[i] >= '0' && STRING[i] <= '9') && STRING[i])
	{
		n = n * 10 + (STRING[i] - '0');
		i++;
	}
	return (n * sign);
}
