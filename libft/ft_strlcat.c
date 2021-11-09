#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	res;

	len1 = ft_strlen(dst);
	len2 = ft_strlen(src);
	i = 0;
	res = 0;
	if (dstsize > len1)
		res = len1 + len2;
	else
		res = len2 + dstsize;
	if (dstsize != 0 && dstsize > len1)
	{
		while (src[i] && (dstsize - len1 - 1) > 0)
		{
			dst[len1] = src[i];
			i++;
			len1++;
		}
		dst[len1] = '\0';
	}
	return (res);
}
