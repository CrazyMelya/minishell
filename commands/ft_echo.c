#include "../minishell.h"

int ft_echo(int argc, char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (argc > 1)
	{
		while (argv[i] && !ft_strncmp(argv[i], "-n", 3))
		{
			flag = 1;
			i++;
		}
		while (argv[i])
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1])
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	free(argv);
	return(SUCCESS);
}
