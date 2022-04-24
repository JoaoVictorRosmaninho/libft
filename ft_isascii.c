/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:59:52 by jv                #+#    #+#             */
/*   Updated: 2022/04/24 14:23:38 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int C)
{
	return (C >= 0 && C < 128);
}
