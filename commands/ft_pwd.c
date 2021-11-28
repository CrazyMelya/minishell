#include "../minishell.h"

int ft_pwd(t_env *env)
{
	printf( "%s\n" ,find_on_head(env, "PWD")->content);
	return(1);
}