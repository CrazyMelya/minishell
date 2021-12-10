/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:42:45 by cliza             #+#    #+#             */
/*   Updated: 2021/12/10 17:05:29 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mywait(pid_t *pid, int size)
{
	int	i;

	i = 0;
	if (g_status != 128)
	{
		while (i < size)
			waitpid(pid[i++], &g_status, 0);
		g_status /= 256;
	}
	else
	{
		while (i < size)
			waitpid(pid[i++], NULL, 0);
		g_status = 1;
	}
}

void	run(t_mini *mini)
{
	pid_t	*pid;
	int		**fd;
	int		size;

	size = minisize(mini);
	if (check_cmd(mini))
		ours_is_first(mini, &size, &fd, &pid);
	else
	{
		pid = malloc(sizeof(pid_t) * size);
		fd = fds_and_pipes_init(size);
		g_status = run_pipe(mini, pid, fd, size);
	}
	mywait(pid, size);
	free_fd_pid(fd, pid);
}

void	free_env(t_env *env)
{
	while (env != NULL)
	{
		free(env->key);
		free(env->content);
		env = env->next;
	}	
}

int	body(t_env *env, char *line)
{
	t_mini	*mini;

	signals_in_cmd();
	add_history(line);
	mini = new_mini(env, 0);
	if (check_line(line))
		return (-1);
	if (ft_parse(line, mini))
	{
		free_mini(mini);
		return (-1);
	}
	run(mini);
	if (mini->ret != -1)
		return (mini->ret);
	free_mini(mini);
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*line;
	int		value;

	argc = 0;
	argv = 0;
	g_status = 0;
	value = -1;
	env = envp_to_list(envp);
	while (1)
	{
		signals_in_main();
		line = readline("😎 \033[0;36m\033[1mminishell ▸ \033[0m");
		if (!line)
			myint3();
		if (line[0] != '\0')
			value = body(env, line);
		if (value != -1)
			return (value);
		free(line);
	}
}
