/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:07:45 by jv                #+#    #+#             */
/*   Updated: 2023/03/25 22:12:50 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void    assert(unsigned char result)
{
    if (result)
        ft_printf(COLOR_BOLD GREEN "OK\n", RESET_COLOR REMOVE_BOLD);
    else
        ft_printf(COLOR_BOLD RED "KO\n", RESET_COLOR REMOVE_BOLD);
}