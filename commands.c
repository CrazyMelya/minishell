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


int ft_echo(t_mini *mini, int flag, int fd)
{
	t_list	*temp;

	temp = mini->arg;
	while (temp)
	{
		ft_putstr_fd(temp->content, fd);
		ft_putchar_fd(' ', fd);
		temp = temp->next;
	}
	if (flag)
		ft_putstr_fd("\n", fd);
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






