/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:28:49 by cliza             #+#    #+#             */
/*   Updated: 2021/12/08 18:17:31 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	detect_len_of_stack(t_env *env)
{
	int	i;

	i = 0;
	if (env == NULL)
		return (i);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

t_env	*new_env(char *key, char *content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = key;
	if (!ft_strcmp(key, "SHLVL"))
	{
		new->content = ft_itoa(ft_atoi(content) + 1);
		free(content);
	}
	else
		new->content = content;
	new->flag = 0;
	new->next = NULL;
	return (new);
}

void	add_env(t_env **env, t_env *new)
{
	t_env	*temp;

	if (!(*env))
		*env = new;
	else
	{
		temp = *env;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

t_env	*envp_to_list(char **envp)
{
	int		i;
	t_env	*env;
	char	*content;
	char	*key;
	int		j;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		key = NULL;
		j = 0;
		while (envp[i][j] != '=')
		{
			key = ft_chrjoin(key, envp[i][j]);
			j++;
		}
		content = NULL;
		j++;
		while (envp[i][j])
			content = ft_chrjoin(content, envp[i][j++]);
		add_env(&env, new_env(key, content));
		i++;
	}
	return (env);
}

char	**envp_arr(t_env *envr)
{
	int		t;
	int		i;
	char	**env_in_list;

	t = 0;
	i = detect_len_of_stack(envr);
	env_in_list = malloc(i * sizeof(char *));
	while (t < i)
	{
		env_in_list[t] = ft_strjoin_env(envr->key, envr->content, '=');
		envr = envr->next;
		t++;
	}
	env_in_list[t] = 0;
	return (env_in_list);
}
