#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	d;

	d = (char )c;
	i = 0;
	if (d == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (1)
	{
		if (s[i] == d)
			return ((char *)&s[i]);
		i++;
		if (s[i] == '\0')
			break ;
	}
	return (NULL);
}
