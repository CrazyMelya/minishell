#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	ind;

	ind = 0;
	if (n == 0)
		return (0);
	while (s1[ind] != '\0' && s1[ind] == s2[ind] && ind < n - 1)
		ind++;
	return ((unsigned char)s1[ind] - (unsigned char)s2[ind]);
}
