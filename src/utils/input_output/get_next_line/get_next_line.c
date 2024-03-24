/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:49:59 by jv                #+#    #+#             */
/*   Updated: 2024/03/23 16:00:04 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

char *read_line(char *buffer, int fd)
{
	ssize_t	size_read;
	char	*line;
	char 	*final;
	char	*tmp;

	size_read = 0;
	if (*buffer == '\0')
	{
		size_read = read(fd, buffer, BUFFER_SIZE);
		if (size_read < 1)
			return (NULL); // read error or EOF
	}
	final = NULL;
	line  = ft_strtok(buffer, "\n");
	if (!line && size_read > 0)
	{
		final = ft_strdup(buffer, NULL);
		while (1)
		{
			tmp = final;
			size_read = read(fd, buffer, BUFFER_SIZE);
			if (size_read < 1) break;
			final = ft_strjoin(final, buffer);
			free(tmp);
		}
	} 
	else
	{
		final = ft_strdup(line, NULL);
		while (line)
		{
			tmp = final;
			line = ft_strtok(buffer, "\n");
			if (line)
			{
				final = ft_strjoin(final, line);
				free(tmp);
			}
		}
		ft_memset(buffer, 0, BUFFER_SIZE + 1);
	}
	tmp = final;
	final = ft_strjoin(final, "\n");
	free(tmp);
	return (final);
}	

char  *get_next_line(int fd)
{
	static char *buffer = NULL;
	char 		*result = NULL;


	if (!buffer)
		buffer = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char), NULL);
	if (!buffer)
		ft_printf("GNL error: alocate buffer error\n");
	result = read_line(buffer, fd);
	if (!result || fd == 0)
	{
		free(buffer);
		buffer = NULL;
		return (result);
	}
	return result;
}
