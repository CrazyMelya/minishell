/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:42:45 by cliza             #+#    #+#             */
/*   Updated: 2021/12/10 17:05:18 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	our_commands(t_mini *mini, char **argv)
{
	if (!ft_strcmp(mini->argv->arg, "echo"))
		g_status = ft_echo(mini->argc, argv);
	else if (!ft_strcmp(mini->argv->arg, "cd"))
		g_status = ft_cd(argv[1], mini->env);
	else if (!ft_strcmp(mini->argv->arg, "pwd"))
		g_status = ft_pwd(mini->env);
	else if (!ft_strcmp(mini->argv->arg, "env"))
		g_status = ft_env(mini->env);
	else if (!ft_strcmp(mini->argv->arg, "export"))
		g_status = ft_export(&mini->env, argv[1]);
	else if (!ft_strcmp(mini->argv->arg, "unset"))
		g_status = ft_unset(&mini->env, argv[1]);
	else if (!ft_strcmp(mini->argv->arg, "env"))
		g_status = ft_env(mini->env);
	else if (!ft_strcmp(mini->argv->arg, "exit"))
		g_status = ft_exit(mini, argv);
	else
	{
		free(argv);
		return (1);
	}
	free(argv);
	return (0);
}

void	other_cmd(t_mini *mini)
{
	char	*path;

	if (!ft_strchr(mini->argv->arg, '/'))
	{
		path = search_path(mini->env, mini->argv->arg);
		if (!path)
		{
			print_error(" : command not found", mini->argv->arg);
			exit(127);
		}
	}
	else
		path = mini->argv->arg;
	if (execve(path, argv_to_arr(mini->argv, mini->argc), envp_arr(mini->env)))
	{
		print_error(" : No such file or directory", mini->argv->arg);
		exit(127);
	}
}

int	ft_pipe(t_mini *mini, int **fds, int n, int size)
{
	if (redir_read(mini, fds, n, size) || redir_write(mini, fds, n, size))
	{
		if (n != -1)
			exit(1);
		else
			return (1);
	}
	if (mini->argv)
	{
		if (n != -1)
			close_fd(fds);
		if (our_commands(mini, argv_to_arr(mini->argv, mini->argc)))
			other_cmd(mini);
		else if (n != -1)
			exit(0);
	}
	return (0);
}

int	run_pipe(t_mini *mini, pid_t *pid, int **fd, int size)
{
	int		i;
	t_mini	*temp;

	if (mini)
	{
		i = 0;
		temp = mini;
		while (i < minisize(temp))
		{
			pid[i] = fork();
			if (pid[i] == -1)
			{
				print_error(" : Resource temporarily unavailable", "fork");
				return (128);
			}
			if (!pid[i])
				ft_pipe(mini, fd, mini->id, size);
			mini = mini->next;
			i++;
		}
	}
	close_fd(fd);
	return (0);
}

void	ours_is_first(t_mini *mini, int *size, int ***fd, pid_t **pid)
{
	int		out;
	int		in;

	out = dup(1);
	in = dup(0);
	*pid = malloc(sizeof(pid_t) * *size - 1);
	*fd = fds_and_pipes_init(*size);
	if (ft_pipe(mini, *fd, -1, *size))
		g_status = 1;
	dup2(out, 1);
	dup2(in, 0);
	close(in);
	close(out);
	g_status = run_pipe(mini->next, *pid, *fd, *size);
	(*size)--;
}
