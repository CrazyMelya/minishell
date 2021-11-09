#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*kuda;

	kuda = malloc(count * size);
	if (kuda)
		ft_memset(kuda, 0, count * size);
	return (kuda);
}
