/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:32:30 by cliza             #+#    #+#             */
/*   Updated: 2021/12/05 03:25:29 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_file(char *filename, int type)
{
	int	fd;

	if (check_dir(filename))
		return (-1);
	if (type)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		print_error(": Permission denied", filename);
		free(filename);
		return (-1);
	}
	close(fd);
	return (0);
}

int	new_write_redir(t_mini *mini, char *filename, int type)
{
	if (check_file(filename, type))
		return (-1);
	if (mini->write_file)
		free(mini->write_file);
	mini->write_file = filename;
	mini->write_type = type;
	return (0);
}

void	add_redir(t_redir **head, char *filename, int type)
{
	t_redir	*temp;

	if (!(*head))
	{
		*head = malloc(sizeof(t_redir));
		(*head)->filename = filename;
		(*head)->type = type;
		(*head)->next = NULL;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = malloc(sizeof(t_redir));
		temp->next->filename = filename;
		temp->next->type = type;
		temp->next->next = NULL;
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
	add_redir(&mini->read_redir, filename, type);
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
