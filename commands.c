/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:28:37 by vbackyet          #+#    #+#             */
/*   Updated: 2021/12/10 17:20:17 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
	{
		write(fd, str, 1);
		str++;
	}
}

void	listprint(t_env *env)
{
	while (env->next != NULL)
	{
		if (env->content != NULL)
			printf("%s=%s\n", env->key, env->content);
		env = env->next;
	}	
	if (env->content != NULL)
		printf("%s=%s\n", env->key, env->content);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	show_env(t_env *envr)
{
	listprint(envr);
}

void	back_flags(t_env *env)
{
	while (env->next != NULL)
	{
		env->flag = 0;
		env = env->next;
	}
	env->flag = 0;
}
