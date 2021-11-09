#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*ss;

	ss = (char *)s;
	len = ft_strlen(s);
	if (c == '\0')
		return (&ss[len]);
	while (len >= 0)
	{
		if (s[len] == c)
			return (&ss[len]);
		len--;
	}
	return (NULL);
}
