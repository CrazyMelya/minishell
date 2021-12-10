/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:28:37 by vbackyet          #+#    #+#             */
/*   Updated: 2021/12/10 17:20:15 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	from_mover(t_env *envr, int i, int *from, char **the_word_of_min)
{
	int	flag;

	if ((sum_of_lett(envr->key, i, envr->flag) == *from))
		flag = 1;
	else
		flag = 0;
	*the_word_of_min = envr->key;
	*from = sum_of_lett(envr->key, i, envr->flag);
	return (flag);
}

char	*find_the_min(t_env *envr, int from, int i, char *the_word_of_min)
{
	int		flag;
	t_env	*beg;

	flag = 0;
	beg = envr;
	while (envr != NULL)
	{
		if (envr->flag != 1)
		{
			if ((sum_of_lett(envr->key, i, envr->flag) <= from) && \
				(sum_of_lett(envr->key, i, envr->flag) != 0))
					flag = from_mover(envr, i, &from, &the_word_of_min);
			else
				envr->flag = -1;
			if ((the_word_of_min == NULL) && (envr->next == NULL))
				the_word_of_min = envr->key;
		}
		envr = envr->next;
	}
	clean_the_stuff(beg, from, i);
	envr = beg;
	if (flag)
		return (NULL);
	return (the_word_of_min);
}

void	half_back_flags(t_env *env)
{
	while (env->next != NULL)
	{
		if (env->flag == -1)
			env->flag = 0;
		env = env->next;
	}
	if (env->flag == -1)
			env->flag = 0;
}

void	show_sorted_env(t_env *envr)
{
	char	*the_min_word;
	int		len_of_the_stack;
	t_env	*the_el;
	int		i;

	len_of_the_stack = detect_len_of_stack(envr);
	while (len_of_the_stack)
	{
		i = 0;
		the_min_word = find_the_min(envr, 100000, i, NULL);
		while (the_min_word == NULL)
		{
			i++;
			the_min_word = find_the_min(envr, 100000, i, NULL);
		}
		half_back_flags(envr);
		the_el = find_on_head(envr, the_min_word);
		(*the_el).flag = 1;
		if (the_el->content)
			printf("declare -x %s=\"%s\"\n", the_el->key, the_el->content);
		else
			printf("declare -x %s\n", the_el->key);
		len_of_the_stack--;
	}
	back_flags(envr);
}

char	**from_list_to_massive(t_env *envr)
{
	int		t;
	int		i;
	char	**env_in_list;

	t = 0;
	i = detect_len_of_stack(envr);
	env_in_list = malloc (i * sizeof(char *));
	while (t < i)
	{		
		env_in_list[t] = ft_strjoin_env(envr->key, envr->content, '=');
		envr = envr->next;
		t++;
	}
	env_in_list[t] = 0;
	return (env_in_list);
}
