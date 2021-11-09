#include "libft.h"

static int	part1(char const *s, char const *what_to_delete)
{
	int		a;
	int		b;
	int		c;

	a = 0;
	b = 0;
	c = 0;
	while (s[a] != 0)
	{
		while (what_to_delete[b] != 0 && c == 0)
		{
			if (s[a] == what_to_delete[b])
				c++;
			b++;
		}
		if (c == 0)
			return (a);
		b = 0;
		c = 0;
		a++;
	}
	return (a);
}

static int	part2(char const *s2, char const *what_to_delete)
{
	int		len;
	int		i;
	int		left_cut;
	int		flag;

	len = ft_strlen(s2) - 1;
	i = 0;
	left_cut = 0;
	flag = 0;
	while (len > 0)
	{
		while (what_to_delete[i] != 0)
		{
			if (s2[len] == what_to_delete[i])
				left_cut++;
			i++;
		}
		flag++;
		len--;
		i = 0;
		if (flag != left_cut)
			return (left_cut);
	}
	return (left_cut);
}

static char	*strcppy(char *kuda, char const *otkuda, int r, int t)
{
	int		i;

	i = 0;
	while (r < t)
	{
		kuda[i] = otkuda[r];
		i++;
		r++;
	}
	kuda[i] = 0;
	return (kuda);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*kuda;
	int		start;
	int		end;
	int		length;
	int		i;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	length = ft_strlen(s1);
	start = part1(s1, set);
	end = part2(s1, set);
	if (start == length)
		kuda = (char *)malloc(sizeof(char) * 1);
	else
		kuda = (char *)malloc(sizeof(char) * (length - (start + end)) + 1);
	if (kuda == 0)
		return (NULL);
	strcppy(kuda, s1, start, length - end);
	return (kuda);
}
