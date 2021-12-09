#include "../minishell.h"

int ft_pwd(t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
		ft_putendl_fd(pwd, 1);
	free(pwd);
	return(0);
}
