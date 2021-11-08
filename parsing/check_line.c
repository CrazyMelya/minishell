/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:58:29 by cliza             #+#    #+#             */
/*   Updated: 2021/11/08 18:30:55 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(char *line)
{
	while (*line)
	{
		if (*line == '\'')
		{
			line++;
			while (*line != '\'')
			{
				if (!(*line))
					return (-1);
				line++;
			}
		}
		if (*line == '\"')
		{
			line++;
			while (*line != '\"')
			{
				if (!(*line))
					return (-1);
				line++;
			}
		}
		line++;
	}
	return (0);
}

int	check_redir(char *line)
{
	while (*line)
	{
		if (*line == '>' || *line == '<')
		{
			line++;
			if (*line == *(line - 1))
				line++;
			while (*line == ' ')
				line++;
			if (ft_strchr(SPEC, *line) || !(*line))
			{
				if (*ft_strchr(SPEC, *line) == '>' && *(line + 1) == '>')
					printf("%s `>>'\n", SYNT_ERR);
				else if (*ft_strchr(SPEC, *line) == '<' && *(line + 1) == '<')
					printf("%s `<<'\n", SYNT_ERR);
				else if (!(*line))
					printf("%s `newline'\n", SYNT_ERR);
				else
					printf("%s `%c'\n", SYNT_ERR, *ft_strchr(SPEC, *line));
				return (-1);
			}			
		}
		line++;
	}
	return (0);
}

int	check_pipe_prefix(char *line)
{
	int	flag;

	flag = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (*line != ' ' && *line != '|')
			flag = 1;
		if (*line == '|')
		{
			if (flag)
				flag = 0;
			else
			{
				printf("bash: syntax error near unexpected token `|'\n");
				return (-1);
			}
			while (*(line + 1) == '|')
				line++;
		}
		line++;
	}
	return (0);
}

int	check_pipe_postfix(char *line)
{
	while (*line)
	{
		if (*line == '|')
		{
			line++;
			while (*line == ' ')
				line++;
			if (!(*line))
			{
				printf("bash: syntax error near unexpected token `|'\n");
				return (-1);
			}
		}
		line++;
	}
	return (0);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ';')
		{
			printf("bash: syntax error near unexpected token `;'\n");
			return (-1);
		}
		i++;
	}
	if (check_quotes(line))
	{
		ft_putstr_fd("bash: syntax error \"quotes is not closed\"\n", 2);
		return (-1);
	}
	if (check_pipe_prefix(line))
		return (-1);
	if (check_pipe_postfix(line))
		return (-1);
	if (check_redir(line))
		return (-1);
	return (0);
}
