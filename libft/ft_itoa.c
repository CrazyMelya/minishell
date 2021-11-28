/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:00:00 by marvin            #+#    #+#             */
/*   Updated: 2021/04/27 11:42:36 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	length(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;

	len = length(n);
	result = (char *) malloc(len + 1);
	if (result == NULL)
		return (NULL);
	if (!n)
		result[0] = '0';
	if (n < 0)
		result[0] = '-';
	result[len] = 0;
	while (n)
	{
		len--;
		if (n > 0)
			result[len] = n % 10 + '0';
		else
			result[len] = '0' - n % 10;
		n /= 10;
	}
	return (result);
}
