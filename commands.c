//написание команд 
// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>
#define SUCCESS 0
// flag - есть -n или нет

void ft_putstr_fd(char *str, int fd)
{
	while(*str)
	{
		write(fd, str, 1);
		str++;
	}

}


int ft_echo(char *str, int flag, int fd)
{
	ft_putstr_fd(str, fd);
	if (flag)
		ft_putstr_fd("\n", fd);
	return(SUCCESS);
}

// int ft_cd(str *path)
// {

// }



int	main(int argc, char **argv, char **env)
{
	char	*str;

	str = readline("bash$ ");
	ft_echo(str, 0 , 1);
	// ft_cd();
	// printf("%s\n", str);
}






