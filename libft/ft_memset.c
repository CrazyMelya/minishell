#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*g;

	g = (char *)b;
	i = 0;
	while (i < len)
	{
		g[i] = c;
		i++;
	}
	return (g);
}
