/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:20:33 by cliza             #+#    #+#             */
/*   Updated: 2021/12/09 21:10:03 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_write(t_mini *mini, int **fds, int n, int size)
{
	int	fd;

	if (mini->write_file)
	{
		if (mini->write_type)
			fd = open(mini->write_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			fd = open(mini->write_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		dup2(fd, 1);
		close(fd);
	}
	else if (size > 1 && n != size - 1)
	{
		if (n == -1)
			dup2(fds[0][1], 1);
		else
			dup2(fds[n][1], 1);
	}
	return (0);
}

void	here_doc(t_mini *mini)
{
	t_redir	*temp;
	char	*line;

	temp = mini->read_redir;
	while (temp)
	{
		if (temp->type)
		{
			if (mini->here_doc[0] != -1)
				close(mini->here_doc[0]);
			pipe(mini->here_doc);
			line = readline("> ");
			while (ft_strncmp(line, temp->filename, ft_strlen(line) + 1))
			{
				ft_putendl_fd(line, mini->here_doc[1]);
				free(line);
				line = readline("> ");
			}
			close(mini->here_doc[1]);
		}
		temp = temp->next;
	}
}

int	read_file(t_mini *mini)
{
	t_redir	*temp;
	int		fd;

	temp = mini->read_redir;
	while (temp)
	{
		if (!temp->type)
		{
			if (check_dir(temp->filename))
				return (1);
			if (access(temp->filename, R_OK))
			{
				if (access(temp->filename, F_OK))
					print_error(": no such file or directory", temp->filename);
				else
					print_error(": Permission denied", temp->filename);
				return (1);
			}
			fd = open(temp->filename, O_RDONLY);
			close(fd);
		}
		temp = temp->next;
	}
	return (0);
}

int	redir_read(t_mini *mini, int **fds, int n, int size)
{
	int		fd;
	t_redir	*temp;

	if (mini->read_redir)
	{
		here_doc(mini);
		if (read_file(mini))
			return (1);
		temp = mini->read_redir;
		while (temp->next)
			temp = temp->next;
		if (temp->type)
			fd = mini->here_doc[0];
		else
		{
			if (mini->here_doc[0] != -1)
				close(mini->here_doc[0]);
			fd = open(temp->filename, O_RDONLY);
		}
		dup2(fd, 0);
		close(fd);
	}
	else if (size > 1 && n > 0)
		dup2(fds[n - 1][0], 0);
	return (0);
}
