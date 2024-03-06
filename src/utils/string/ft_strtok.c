/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:44:06 by jv                #+#    #+#             */
/*   Updated: 2024/03/05 23:24:41 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

static void ft_flush(char **tok, char **current_position)
{
	if (*tok)
		free(*tok);
	*tok = NULL;
	if (current_position)
		*current_position = NULL;
}



char *ft_strtok(char *str, const char *delimiter)
{
	static char 	*current_tok = NULL;
	static char 	*current_position = NULL;
	char 			*start;
	unsigned int 	size;

	if (!str || !delimiter)
		return (NULL);
	if (!current_position)
		current_position = str;
	if (!(*current_position))
	{
		ft_flush(&current_tok, &current_position);
		return (NULL);
	}
	start = current_position;
	size =  ft_strlen(delimiter);
	while (*current_position && ft_strncmp(current_position, delimiter, size) != 0)
		current_position++;
	if (!(*current_position) && !current_tok)
	{
		ft_flush(&current_tok, &current_position);
		return (NULL); 
	}
	if (current_tok != NULL) ft_flush(&current_tok, NULL);
	current_tok = (char *) ft_calloc((current_position - start) + 1, sizeof(char), NULL);
	ft_strlcpy(current_tok, start, current_position - start + 1);
	if ((*current_position)) current_position += size;
	return (current_tok);
}