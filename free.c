/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 01:58:05 by cliza             #+#    #+#             */
/*   Updated: 2021/12/07 15:59:57 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
}

void	free_redir(t_redir *redir)
{
	t_redir	*temp;

	while (redir)
	{
		free(redir->filename);
		temp = redir->next;
		free(redir);
		redir = temp;
	}
}

void	free_argv(t_argv *argv)
{
	t_argv	*temp;

	while (argv)
	{
		free(argv->arg);
		temp = argv->next;
		free(argv);
		argv = temp;
	}
}

void	free_mini(t_mini *mini)
{
	t_mini	*temp;

	while (mini)
	{
		free_argv(mini->argv);
		free_redir(mini->read_redir);
		free(mini->write_file);
		temp = mini->next;
		free(mini);
		mini = temp;
	}
}

void	free_fd_pid(int **fd, pid_t *pid)
{
	int	i;

	i = 0;
	while (fd[i])
		free(fd[i++]);
	free(fd);
	free(pid);
}
