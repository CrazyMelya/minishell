/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 21:29:04 by marvin            #+#    #+#             */
/*   Updated: 2021/04/25 22:48:30 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*dest_temp;
	const char	*src_temp;

	dest_temp = (char *)dest;
	src_temp = (const char *)src;
	while (n--)
	{
		*dest_temp = *src_temp;
		if (*dest_temp == (char)c)
			return (++dest_temp);
		dest_temp++;
		src_temp++;
	}
	return (NULL);
}
