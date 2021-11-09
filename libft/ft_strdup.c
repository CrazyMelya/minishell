#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*kuda;
	int		i;

	kuda = malloc(ft_strlen(src) + 1);
	if (!kuda)
		return (NULL);
	i = 0;
	while (src[i])
	{
		kuda[i] = src[i];
		i++;
	}
	kuda[i] = '\0';
	return (kuda);
}
