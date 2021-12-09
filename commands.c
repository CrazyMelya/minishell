/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:28:37 by vbackyet          #+#    #+#             */
/*   Updated: 2021/12/09 19:35:19 by vbackyet         ###   ########.fr       */
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

void	paste_env(t_env *export, t_env **envr)
{
	t_env	*temp;
	int		i;

	temp = *envr;
	while (temp-> next != NULL)
	{
		if (ft_strcmp(temp->key, export->key) == 0)
		{
			if (!export->content)
			{
				free (export->key);
				free (export->content);
				free (export);
				return ;
			}
			temp->content = export->content;
			return ;
		}
		temp = temp->next;
	}	
	if (ft_strcmp(temp->key, export->key) == 0)
	{
		if (!export->content)
		{
			free (export->key);
			free (export->content);
			free (export);
			return ;
		}
		temp->content = export->content;
		return ;		
	}
	temp->next = export;
}

static	int	detect_len_of_stack(t_env *stack)
{
	int	i;

	i = 0;
	if (stack == NULL)
		return (0);
	while (stack->next != NULL)
	{
		i++;
		stack = stack-> next;
	}
	return (i + 1);
}


int	sum_of_lett(char *my_word, int to, int flag)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while ((my_word[i] != '\0') && (i <= to))
	{
		sum += (int)my_word[i];
		i++;
	}
	if (flag == -1)
		return (0);
	return (sum);
}

void	clean_the_stuff(t_env *beg, int from, int i)
{
	while (beg != NULL)
	{
		if ((sum_of_lett(beg->key, i, beg->flag) > from) && \
		(sum_of_lett(beg->key, i, beg->flag) != 0))
		{
			if (beg->flag != 1)
				beg->flag = -1;
		}
		beg = beg-> next;
	}
}

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

void	back_flags(t_env *env)
{
	while (env->next != NULL)
	{
		env->flag = 0;
		env = env->next;
	}
	env->flag = 0;
}


void half_back_flags(t_env *env)
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
