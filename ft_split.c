/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:51:56 by jv                #+#    #+#             */
/*   Updated: 2022/04/21 17:47:29 by jv               ###   ########.fr       */
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

static void	get_split(char **bipointer, const char *s, char c)
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

	if (!s || !c || ft_strlen(s) < 1)
		return (NULL);
	delimiters = ft_count_char(s, c) + 1;
	bipointer = (char **) ft_calloc(delimiters + 1, sizeof(char *));
	if (!bipointer)
		return (NULL);
	get_split(bipointer, s, c);
	return (bipointer);
}

/*
static int	ft_split_is_word(char const *s, char c, size_t i)
{
	if (s[i] != c)
		if (i == 0 || (i > 0 && s[i - 1] == c))
			return (1);
	return (0);
}

static size_t	ft_split_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count_words;

	i = 0;
	count_words = 0;
	while (s[i] != '\0')
	{
		if (ft_split_is_word(s, c, i) == 1)
			count_words++;
		i++;
	}
	return (count_words);
}

static size_t	ft_split_next_word(char const *s, char c, size_t idword)
{
	size_t	i;

	i = idword;
	while (ft_split_is_word(s, c, i) == 0 && s[i] != '\0')
		i++;
	return (i);
}

static size_t	ft_split_count_characters(char const *sc, char c, size_t i)
{
	size_t	count_c;

	count_c = 0;
	while (sc[i + count_c] != c && sc[i + count_c] != '\0')
		count_c++;
	return (count_c);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	count_c;
	size_t	count_w;
	size_t	idword;
	char	**splited;

	if (s == NULL)
		return (NULL);
	count_w = ft_split_count_words(s, c);
	splited = (char **) malloc(sizeof(char *) * (count_w + 1));
	if (splited == NULL)
		return (NULL);
	idword = -1;
	i = -1;
	while (++i < count_w)
	{
		idword = ft_split_next_word(s, c, ++idword);
		count_c = ft_split_count_characters(s, c, idword);
		splited[i] = (char *) malloc(sizeof(char) * (count_c + 1));
		if (splited[i] == NULL)
			return (NULL);
		ft_strlcpy(splited[i], &s[idword], count_c + 1);
	}
	splited[count_w] = NULL;
	return (splited);
}
*/