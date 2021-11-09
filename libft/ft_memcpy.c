#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dstt;
	char	*srcc;

	dstt = (char *)dst;
	srcc = (char *)src;
	if (n > 0 && (dstt || srcc))
	{
		n = n - 1;
		while (n > 0)
		{
			dstt[n] = srcc[n];
			n--;
		}
		dstt[n] = srcc[n];
	}
	return (dst);
}
