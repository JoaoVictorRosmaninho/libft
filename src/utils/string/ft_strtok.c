/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:44:06 by jv                #+#    #+#             */
/*   Updated: 2023/03/20 09:10:07 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"


char *ft_strtok(char *str, cost char *delimiter, int ignore_quote)
{
	static char *current_tok = NULL;
	static char *current_position = str;
	char *start;
	unsigned int size;


    if (!str || !delimiter)
        return (NULL);
	start = current_position;

	size - ft_strlen(delimiter);

	while (*current_position && ft_strncmp(current_position, delimiter, size) != 0)
		current_position++;
	current_position += size;
	
	current_tok = (char *) ft_calloc((current_position - start) + 1, sizeof(char));
	ft_strlcpy(current_tok, current_position, current_position - start + 1);

	return (current_tok);
}