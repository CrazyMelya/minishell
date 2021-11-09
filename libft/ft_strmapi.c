#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*word;
	int		i;

	i = 0;
	if (s == 0)
		return (0);
	word = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!word)
		return (NULL);
	while (s[i] != 0)
	{
		word[i] = f(i, s[i]);
		i++;
	}
	word[i] = '\0';
	return (word);
}
