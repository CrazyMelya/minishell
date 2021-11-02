/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 10:21:23 by marvin            #+#    #+#             */
/*   Updated: 2021/04/25 22:34:42 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	char		*dest_temp;
	const char	*src_temp;

	if (!dest && !src)
		return (NULL);
	dest_temp = (char *)dest;
	src_temp = (const char *)src;
	if (dest < src)
	{
		while (n--)
			*dest_temp++ = *src_temp++;
	}
	else
	{
		while (n)
		{
			dest_temp[n - 1] = src_temp[n - 1];
			n--;
		}
	}
	return (dest);
}
