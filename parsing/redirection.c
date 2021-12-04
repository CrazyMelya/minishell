/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:32:30 by cliza             #+#    #+#             */
/*   Updated: 2021/12/03 23:31:22 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_file(t_mini *mini, char *filename)
{
	int	fd;

	if (check_dir(filename))
		return (-1);
	if (mini->write_type)
		fd = open(mini->write_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(mini->write_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		printf("😎 \033[0;36m\033[1mminishell ▸ \033[0m%s: Permission denied\n", mini->write_file);
		free(filename);
		return (-1);
	}
	close(fd);
	return (0);
}

int	new_write_redir(t_mini *mini, char *filename, int type)
{
	if (mini->write_file)
	{
		if (check_file(mini, filename))
			return (-1);
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
