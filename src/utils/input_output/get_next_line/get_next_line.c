/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:49:59 by jv                #+#    #+#             */
/*   Updated: 2024/11/23 15:13:02 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

char *read_line(char *buffer, int fd, t_coliseu* coliseu)
{
	char	*line     = NULL;
	char 	*final    = NULL;

	ssize_t bytes = 0;

	char* toker = NULL;

	if (ft_strlen(buffer) > 0 ) {
		if ( ( line = ft_strtok(buffer, "\n", &toker, coliseu) ) != NULL ) {
			size_t size_line = ft_strlen(line);
			ft_strlcpy(buffer,  buffer + size_line + 1, BUFFER_SIZE);
			return final ? ft_strjoin(final, line, coliseu) : ft_strdup(line, coliseu);
		} 
		
		final = final ? ft_strjoin(final, buffer, coliseu) : ft_strdup(buffer, coliseu);		
	} 
	
	ft_bzero(buffer, BUFFER_SIZE);

	while ( ( bytes = read(fd, buffer, BUFFER_SIZE - 1) ) > 0 ) {
		
		buffer[bytes] = '\0';

		if ( ( line = ft_strtok(buffer, "\n", &toker, coliseu) ) != NULL ) {
			size_t size_line = ft_strlen(line);
			ft_strlcpy(buffer,  buffer + size_line + 1, BUFFER_SIZE);
			return final ? ft_strjoin(final, line, coliseu) : ft_strdup(line, coliseu);
		}

		final = final ? ft_strjoin(final, buffer, coliseu) : ft_strdup(buffer, coliseu);		
			
		ft_memset(buffer, 0, BUFFER_SIZE);
	} 
	return (final);
}	

char  *get_next_line(int fd, t_coliseu* coliseu)
{
	static char  buffer[BUFFER_SIZE] = { 0 };
	char 		*result = NULL;

	if (fd == 0) return (result);

	result = read_line(buffer, fd, coliseu);
	return result;
}
