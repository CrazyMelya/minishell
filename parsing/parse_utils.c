/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:08:02 by cliza             #+#    #+#             */
/*   Updated: 2021/12/06 16:20:30 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_arg(t_argv **argv, char	*arg)
{
	t_argv	*temp;

	temp = *argv;
	if (!(*argv))
	{
		*argv = malloc(sizeof(t_argv));
		(*argv)->arg = arg;
		(*argv)->next = NULL;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = malloc(sizeof(t_argv));
		temp->next->arg = arg;
		temp->next->next = NULL;
	}
}

char	*ft_chrjoin(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(ft_strlen(str) + 2);
	if (str)
	{
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	}
	new[i++] = c;
	new[i] = 0;
	free(str);
	return (new);
}

char	*search_key(char **key, t_env *env)
{
	if (**key == '$')
	{
		(*key)++;
		return (ft_itoa(getpid()));
	}
	if (**key == '?')
	{
		(*key)++;
		return (ft_itoa(g_status));
	}
	while (env)
	{
		if (!ft_strncmp(*key, env->key, ft_strlen(*key) + 1))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

int	print_redir_error(char **line)
{
	if (**line == *(*line + 1))
		(*line)++;
	(*line)++;
	while (**line == ' ')
		(*line)++;
	if (!(**line) || ft_strchr(SPEC2, **line))
	{
		if (*ft_strchr(SPEC2, **line) == '>' && *(*line + 1) == '>')
			printf("%s `>>'\n", SYNT_ERR);
		else if (*ft_strchr(SPEC2, **line) == '<' && *(*line + 1) == '<')
			printf("%s `<<'\n", SYNT_ERR);
		else if (!(**line))
			printf("%s `newline'\n", SYNT_ERR);
		else
			printf("%s `%c'\n", SYNT_ERR, *ft_strchr(SPEC2, **line));
		return (-1);
	}
	return (0);
}

void	quotes(t_mini *mini, char **line, char **arg)
{
	if (**line == '\'')
		single_quotes(line, arg);
	else
		double_quotes(mini, line, arg);
}
