//написание команд 
// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

#include "minishell.h"
#define SUCCESS 0
// flag - есть -n или нет

//void ft_putstr_fd()
//{

//}

int	argc(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

int ft_echo(char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (argc(argv) > 1)
	{
		while (argv[i] && !ft_strncmp(argv[i], "-n", 3))
		{
			flag = 1;
			i++;
		}
		//if (!ft_strncmp(argv[i], "-", 2))
		//	i++;
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
	return(SUCCESS);
}

//int ft_cd(str *path)
//{

//}



// int	main(int argc, char **argv, char **env)
// {
// 	char	*str;

// 	str = readline("bash$ ");
// 	ft_echo(str, 0);
// 	ft_cd();
// 	// printf("%s\n", str);
// }






