#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		i;
	char	a;

	a = '\n';
	i = 0;
	if (s == 0)
		return ;
	while (s[i] != 0)
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, &a, 1);
}
