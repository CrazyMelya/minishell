/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:32:30 by cliza             #+#    #+#             */
/*   Updated: 2021/11/08 19:39:01 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_write_redir(t_mini *mini, char *filename, int type)
{
	int	fd;

	if (mini->write_file)
	{
		if (mini->write_type)
			fd = open(mini->write_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			fd = open(mini->write_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		close(fd);
		free(mini->write_file);
		mini->write_file = filename;
		mini->write_type = type;
	}
	else
	{
		mini->write_file = filename;
		mini->write_type = type;
	}
}

int	new_read_redir(t_mini *mini, char *filename)
{
	int	fd;

	if (mini->read_file)
	{
		if (!mini->read_type)
		{
			fd = open(mini->read_file, O_RDONLY);
			if (fd == -1)
			{
				printf("bash: %s: No such file or directory\n",
					mini->read_file);
				return (-1);
			}
			close(fd);
		}
		free(mini->read_file);
		mini->read_file = filename;
	}
	else
	{
		mini->read_file = filename;
		if (mini->read_type == -1)
			mini->read_type = 0;
	}
	return (0);
}

int	read_redir(t_mini *mini, char **line)
{
	char	*filename;

	filename = NULL;
	(*line)++;
	if (**line == '<')
		(*line)++;
	while (**line == ' ')
		(*line)++;
	while (**line != ' ' && **line)
	{
		filename = ft_chrjoin(filename, **line);
		(*line)++;
	}
	return (new_read_redir(mini, filename));
}

void	write_redir(t_mini *mini, char **line)
{
	char	*filename;
	int		type;

	filename = NULL;
	(*line)++;
	if (**line == '>')
	{
		type = 1;
		(*line)++;
	}
	else
		type = 0;
	while (**line == ' ')
		(*line)++;
	while (**line != ' ' && **line)
	{
		filename = ft_chrjoin(filename, **line);
		(*line)++;
	}
	new_write_redir(mini, filename, type);
}
