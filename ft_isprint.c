/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:01:07 by jv                #+#    #+#             */
/*   Updated: 2022/04/09 22:02:45 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int C)
{
	return (!((C < 32) || (C > 126)));
}
