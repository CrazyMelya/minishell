#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	a;
	char	*kuda;

	if (!s)
		return (0);
	i = 0;
	a = 0;
	kuda = (char *)malloc(sizeof(*s) * (len + 1));
	if (!kuda)
		return (NULL);
	while (s[i] != '\0')
	{
		if (i >= start && a < len)
		{
			kuda[a] = s[i];
			a++;
		}
		i++;
	}
	kuda[a] = '\0';
	return (kuda);
}
