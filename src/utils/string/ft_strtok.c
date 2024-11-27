/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:44:06 by jv                #+#    #+#             */
/*   Updated: 2024/11/23 15:30:01 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

static void ft_flush(char **tok, char **current_position)
{
	*tok = NULL;
	if (current_position) *current_position = NULL;
}



char *ft_strtok(char *str, const char *delimiter, char** string_ptr, t_coliseu* coliseu)
{
	static char 	*current_tok      = NULL;
	char 			*start;
	unsigned int 	size;

	if (!str || !delimiter)
		return (NULL);
	if (!*string_ptr)
		*string_ptr = str;
	if (!(**string_ptr))
	{
		ft_flush(&current_tok, string_ptr);
		return (NULL);
	}
	start = *string_ptr;
	size =  ft_strlen(delimiter);
	while (**string_ptr && ft_strncmp(*string_ptr, delimiter, size) != 0)
		(*string_ptr)++;
	if (!(**string_ptr) && !current_tok && ((*string_ptr - start) < 1))
	{
		ft_flush(&current_tok, string_ptr);
		return (NULL); 
	}
	
	if (current_tok != NULL) ft_flush(&current_tok, NULL);

	current_tok = (char *) ft_calloc((*string_ptr - start) + 1, sizeof(char), coliseu);
	
	ft_strlcpy(current_tok, start, *string_ptr - start + 1);

	while (ft_strncmp(*string_ptr, delimiter, size) == 0) 
		*string_ptr += 1;
		
	return (current_tok);
}