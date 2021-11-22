/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:32:30 by cliza             #+#    #+#             */
/*   Updated: 2021/11/15 17:26:13 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	new_write_redir(t_mini *mini, char *filename, int type)
{
	int	fd;

	if (mini->write_file)
	{
		if (mini->write_type)
			fd = open(mini->write_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			fd = open(mini->write_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
		{
			printf("bash: %s: No such file or directory\n",
				mini->write_file);
			return (-1);
		}
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
	return (0);
}

t_redir	*new_redir(char *filename, int type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	new->filename = filename;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_redir(t_redir **head, t_redir *new)
{
	t_redir	*temp;

	if (!(*head))
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	read_redir(t_mini *mini, char **line)
{
	char	*filename;
	int		type;

	filename = NULL;
	(*line)++;
	type = 0;
	if (**line == '<')
	{
		(*line)++;
		type = 1;
	}
	while (**line == ' ')
		(*line)++;
	while (**line != ' ' && **line && **line != '|')
	{
		filename = ft_chrjoin(filename, **line);
		(*line)++;
	}
	add_redir(&mini->read_redir, new_redir(filename, type));
}

int	write_redir(t_mini *mini, char **line)
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
	while (**line != ' ' && **line && **line != '|')
	{
		filename = ft_chrjoin(filename, **line);
		(*line)++;
	}
	return (new_write_redir(mini, filename, type));
}
