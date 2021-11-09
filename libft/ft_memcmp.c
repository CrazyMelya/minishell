#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src;

	dst = (unsigned char *) s1;
	src = (unsigned char *) s2;
	while (n--)
	{
		if (*src != *dst)
			return (*dst - *src);
		src++;
		dst++;
	}
	return (0);
}
