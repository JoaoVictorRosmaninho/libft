/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:51:56 by jv                #+#    #+#             */
/*   Updated: 2022/04/10 14:58:36 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static unsigned int	ft_count_char(const char *s, char c)
{
	unsigned int	delimiter;
	unsigned int	index;

	delimiter = 0;
	index = 0;
	while (s[index])
	{
		if (s[index] == c)
			delimiter++;
		index++;
	}
	return (delimiter);
}

void	get_split(char **bipointer, const char *s, char c)
{
	unsigned int	ini;
	unsigned int	end;
	unsigned int	index;

	ini = 0;
	end = 0;
	index = 0;
	while (s[end])
	{
		if (s[end] == c)
		{
			if ((end - ini) < 1)
			{
				end++;
				ini++;
				continue ;
			}
			bipointer[index++] = ft_substr(s, ini, (end - ini));
			ini = end + 1;
		}
		end++;
	}
	bipointer[index++] = ft_substr(s, ini, (end - ini));
}

char	**ft_split(const char *s, char c)
{
	unsigned int	delimiters;
	char			**bipointer;

	if (!s || !c)
		return (NULL);
	delimiters = ft_count_char(s, c) + 1;
	bipointer = (char **) ft_calloc(delimiters + 1, sizeof(char *));
	if (!bipointer)
		return (NULL);
	get_split(bipointer, s, c);
	return (bipointer);
}
