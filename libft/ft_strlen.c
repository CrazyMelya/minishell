#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;
	char	*r;

	r = (char *)s;
	len = 0;
	while (r[len] != '\0')
	{
		len++;
	}
	return (len);
}
