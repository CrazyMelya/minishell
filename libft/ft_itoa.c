#include "libft.h"

static int	count_sym(long int nb)
{
	int		counter;

	counter = 0;
	if (nb < 0)
	{
		counter++;
		nb *= -1;
	}
	if (nb == 0)
		return (1);
	while (nb >= 1)
	{
		counter++;
		nb /= 10;
	}
	return (counter);
}

static char	*perform(long int nb, int len, char *memory)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		i++;
		nb *= -1;
	}
	memory[len] = '\0';
	while (--len)
	{
		memory[len] = (nb % 10) + '0';
		nb /= 10;
	}
	if (i != 0)
		memory[0] = '-';
	else
		memory[0] = (nb % 10) + '0';
	return (memory);
}

char	*ft_itoa(int n)
{
	int			my_len;
	long int	num;
	char		*place;

	num = (long int)n;
	my_len = count_sym(num);
	place = (char *)malloc(sizeof(char) * (my_len + 1));
	if (!place)
		return (0);
	place = perform(num, my_len, place);
	return (place);
}
