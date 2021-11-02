/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:37:57 by marvin            #+#    #+#             */
/*   Updated: 2021/04/27 12:51:33 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	i;
	size_t			s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		result = malloc(1);
		result[0] = 0;
		return (result);
	}
	if (s_len < len)
		len = s_len;
	result = (char *)malloc(len + 1);
	if (result == NULL)
		return (result);
	i = 0;
	while (i < len && start < s_len)
		result[i++] = s[start++];
	result[i] = 0;
	return (result);
}
