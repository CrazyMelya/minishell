#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i++ < n)
	{
		if (*(const unsigned char *)arr == (unsigned char) c)
			return ((char *)arr);
		arr++;
	}
	return (NULL);
}
