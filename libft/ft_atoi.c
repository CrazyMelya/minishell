#include "libft.h"

int	prov(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
		str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int				res;
	int				sign;
	unsigned int	i;

	res = 0;
	sign = 1;
	i = prov(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == -1 && ((res == 214748364 && str[i] - '0' > 8) || \
			res > 214748364))
			return (0);
		if (sign == 1 && ((res == 214748364 && str[i] - '0' > 7) || \
			res > 214748364))
			return (-1);
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}
