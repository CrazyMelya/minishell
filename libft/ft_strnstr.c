#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	sub_i;

	i = 0;
	if (ft_strncmp(needle, "", 100) == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		sub_i = 0;
		while (i + sub_i < len && haystack[i + sub_i] == needle[sub_i] &&\
		needle[sub_i] != '\0')
			sub_i++;
		if (needle[sub_i] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
