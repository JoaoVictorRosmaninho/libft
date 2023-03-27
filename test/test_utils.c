/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:07:45 by jv                #+#    #+#             */
/*   Updated: 2023/03/26 20:08:04 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void    assert(unsigned char result)
{
    if (result)
    {
        ft_printf(COLOR_BOLD GREEN "OK ", RESET_COLOR REMOVE_BOLD);
        ft_printf(RESET_COLOR);
    }
    else
    {
        ft_printf(COLOR_BOLD RED "KO ", RESET_COLOR REMOVE_BOLD);
        ft_printf(RESET_COLOR);
    }
}