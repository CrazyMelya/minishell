/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:52:09 by vbackyet          #+#    #+#             */
/*   Updated: 2021/12/09 21:28:56 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strisnum(char *word)
{
	if (ft_atoi(word) == -1)
		return (0);
	if (*word == '+')
		word++;
	while (*word)
	{
		if (!ft_isdigit(*word))
			return (0);
		word++;
	}
	return (1);
}

int	ft_exit(t_mini *mini, char **array)
{
	if (array[1] && ft_strisnum(array[1]) == 0)
	{
		mini->ret = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(array[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (array[1] && array[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	else if (array[1])
		mini->ret = ft_atoi(array[1]);
	else
		mini->ret = 0;
	return (0);
}
