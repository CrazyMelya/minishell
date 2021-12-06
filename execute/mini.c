/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:26:32 by cliza             #+#    #+#             */
/*   Updated: 2021/12/05 06:28:01 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mini	*new_mini(t_env *env, int id)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	mini->argc = 0;
	mini->argv = NULL;
	mini->write_file = NULL;
	mini->write_type = -1;
	mini->env = env;
	mini->next = NULL;
	mini->read_redir = NULL;
	mini->here_doc[0] = -1;
	mini->id = id;
	mini->ret = -1;
	return (mini);
}

int	minisize(t_mini	*mini)
{
	int	i;

	i = 1;
	while (mini->next)
	{
		mini = mini->next;
		i++;
	}
	return (i);
}

char	**argv_to_arr(t_argv *argv, int argc)
{
	char	**result;
	int		i;

	result = malloc(sizeof(char *) * (argc + 1));
	i = 0;
	while (i < argc)
	{
		result[i] = argv->arg;
		i++;
		argv = argv->next;
	}
	result[i] = NULL;
	return (result);
}
