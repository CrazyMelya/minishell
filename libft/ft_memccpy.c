#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char	*dstt;
	char	*srcc;
	char	cc;
	size_t	i;

	i = 0;
	cc = (char) c;
	dstt = (char *)dst;
	srcc = (char *)src;
	while (n--)
	{
		*dstt++ = *srcc++;
		if (*(dstt - 1) == cc)
			return (dstt);
	}
	return (NULL);
}
