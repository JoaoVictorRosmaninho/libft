/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:58:02 by jv                #+#    #+#             */
/*   Updated: 2023/03/26 18:56:53 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# include "../includes/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"
# define RESET_COLOR "\x1B[0m"
# define COLOR_BOLD "\e[1m"
# define REMOVE_BOLD "\e[m"

// Utils for tests
void    assert(unsigned char result);



// tests 

void	get_next_line_test(void);
void	ft_strtok_test(void);

#endif
