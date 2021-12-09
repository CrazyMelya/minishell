#include "../minishell.h"

int ft_strisnum(char *word)
{
	while(*word)
	{
		if (ft_isalpha(*word))
			return(0);
		word++;
	}
	return(1);
}


void	ft_exit(t_mini *mini, char **array)
{
	// ft_putstr_fd("exit\n", 2);
	if (array[1] && array[2])
	{
		g_status = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else if (array[1] && ft_strisnum(array[1]) == 0)
	{
		mini->ret = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(array[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (array[1])
		mini->ret = ft_atoi(array[1]);
	else
		mini->ret = 0;
}
