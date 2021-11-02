/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 23:20:49 by marvin            #+#    #+#             */
/*   Updated: 2021/04/26 10:10:06 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_counter(char const *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != c)
			|| (s[i] == c && s[i + 1] != c && s[i + 1] != 0))
			n++;
		i++;
	}
	return (n);
}

static char	**free_words(int n, char **array)
{
	int	i;

	i = 0;
	while (i < n)
		free(array[i++]);
	free(array);
	array = NULL;
	return (NULL);
}

static char	**mk_split(char const *s, char c, int words)
{
	char	**result;
	int		n;
	int		j;

	result = (char **)malloc((words + 1) * sizeof(char **));
	if (result == NULL)
		return (NULL);
	n = 0;
	while (words--)
	{
		j = 0;
		while (*s == c && *s)
			s++;
		while (s[j] != c && s[j])
			j++;
		result[n] = ft_substr(s, 0, j);
		if (result[n] == NULL)
			return (free_words(n, result));
		n++;
		s = &s[j];
	}
	result[n] = 0;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		words;

	if (!s)
		return (NULL);
	words = words_counter(s, c);
	return (mk_split(s, c, words));
}
