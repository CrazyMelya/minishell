/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:58:29 by cliza             #+#    #+#             */
/*   Updated: 2021/11/09 21:05:24 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes_semicolon(char *line)
{
	char	q;

	while (*line)
	{
		if (*line == ';')
			return (-1);
		if (*line == '\'' || *line == '\"')
		{
			q = *line;
			line++;
			while (*line != q)
			{
				if (!(*line))
					return (-2);
				line++;
			}
		}
		line++;
	}
	return (0);
}

int	check_redir(char *line)
{
	int		flag;
	char	q;

	flag = 0;
	while (*line)
	{
		if (flag == 0 && (*line == '\'' || *line == '\"'))
		{
			q = *line++;
			flag = 1;
		}
		if (flag == 0 && (*line == '>' || *line == '<'))
		{
			if (print_redir_error(&line))
				return (-1);
		}
		if (flag && *line == q)
			flag = 0;
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
			while (*line == '|')
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
	if (check_quotes_semicolon(line) == -1)
	{
		printf("bash: syntax error near unexpected token `;'\n");
		return (-1);
	}
	else if (check_quotes_semicolon(line) == -2)
	{
		printf("bash: syntax error `unclosed quotes'\n");
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
