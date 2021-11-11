/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:07:08 by cliza             #+#    #+#             */
/*   Updated: 2021/11/11 19:21:40 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_dollar(t_mini *mini, char **line, char **arg)
{
	char	*key;
	char	*temp;

	key = NULL;
	(*line)++;
	if (**line != '$' && **line != '?')
	{
		while (**line && !ft_strchr(SPEC, **line))
		{
			key = ft_chrjoin(key, **line);
			(*line)++;
		}
	}
	else
	{
		key = ft_strdup(*line);
		(*line)++;
	}
	temp = *arg;
	*arg = ft_strjoin(*arg, search_key(key, mini->env));
	free(temp);
	free(key);
	return ;
}

void	single_quotes(char **line, char **arg)
{
	(*line)++;
	while (**line != '\'')
	{
		*arg = ft_chrjoin(*arg, **line);
		(*line)++;
	}
	(*line)++;
}

void	double_quotes(t_mini *mini, char **line, char **arg)
{
	(*line)++;
	while (**line != '\"' && **line)
	{
		if (**line == '$')
			parse_dollar(mini, line, arg);
		else
		{
			*arg = ft_chrjoin(*arg, **line);
			(*line)++;
		}	
	}
	(*line)++;
}

int	parse_continue(t_mini **mini, char *arg, char **line)
{
	if (arg)
	{
		(*mini)->argv = add_arg((*mini)->argc, (*mini)->argv, arg);
		(*mini)->argc++;
	}
	if (**line == '>')
	{
		if (write_redir(*mini, line))
			return (-1);
	}
	else if (**line == '<')
		read_redir(*mini, line);
	else if (**line == '|')
	{
		while (**line == '|')
			(*line)++;
		(*mini)->next = new_mini((*mini)->env);
		*mini = (*mini)->next;
	}
	(*line)++;
	return (0);
}

int	ft_parse(char *line, t_mini *mini)
{
	char	*arg;

	while (*line)
	{
		arg = NULL;
		while (*line == ' ')
			line++;
		while (!ft_strchr(SPEC2, *line) && *line)
		{
			if (*line == '$' && *(line + 1) && !ft_strchr(SPEC3, *(line + 1)))
				parse_dollar(mini, &line, &arg);
			else if (*line == '\'')
				single_quotes(&line, &arg);
			else if (*line == '\"')
				double_quotes(mini, &line, &arg);
			else
			{
				arg = ft_chrjoin(arg, *line);
				line++;
			}
		}
		if (parse_continue(&mini, arg, &line))
			return (-1);
	}
	return (0);
}
