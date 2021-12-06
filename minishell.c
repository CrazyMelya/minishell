/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:42:45 by cliza             #+#    #+#             */
/*   Updated: 2021/12/06 16:22:32 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_mini(t_mini *mini)
{
	int		i;
	t_redir	*temp;
	t_argv	*temp2;

	i = 0;
	if (mini->argv)
	{
		printf("%i ", mini->argc);
		temp2 = mini->argv;
		while (temp2)
		{
			printf("%i %s ", i, temp2->arg);
			temp2 = temp2->next;
			i++;
		}
	}
	if (mini->write_file)
	{
		printf("| %s ", mini->write_file);
		if (mini->write_type == 1)
			printf(" >> |");
		else if (!mini->write_type)
			printf(" > |");
	}
	temp = mini->read_redir;
	while (temp)
	{
		printf("| %s ", temp->filename);
		if (temp->type == 1)
			printf(" << |");
		else
			printf(" < |");
			temp = temp->next;
	}
	printf("\n");
}

int	our_commands(t_mini *mini)
{
	if (!ft_strncmp(mini->argv->arg, "echo", 5))
		ft_echo(mini->argc, argv_to_arr(mini->argv, mini->argc));
	else if (!ft_strncmp(mini->argv->arg, "cd", 3))
		ft_cd(argv_to_arr(mini->argv, mini->argc)[1], mini->env);
	else if (!ft_strncmp(mini->argv->arg, "pwd", 4))
		ft_pwd(mini->env);
	else if (!ft_strncmp(mini->argv->arg, "env", 4))
		ft_env(mini->env);
	else if (!ft_strncmp(mini->argv->arg, "export", 7))
		ft_export(&mini->env, argv_to_arr(mini->argv, mini->argc)[1]);
	else if (!ft_strncmp(mini->argv->arg, "unset", 6))
		ft_unset(&mini->env, argv_to_arr(mini->argv, mini->argc)[1]);
	else if (!ft_strncmp(mini->argv->arg, "env", 4))
		ft_env(mini->env);
	else if (!ft_strncmp(mini->argv->arg, "exit", 5))
		ft_exit(mini, argv_to_arr(mini->argv, mini->argc));
	else
		return (1);
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
	if (n != -1)
		close_fd(fds);
	if (our_commands(mini))
		other_cmd(mini);
	else if (n != -1)
		exit(0);
	else
		g_status = 0;
	return (0);
}

void	run_pipe(t_mini *mini, pid_t *pid, int **fd, int size)
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
			if (!pid[i])
				ft_pipe(mini, fd, mini->id, size);
			mini = mini->next;
			i++;
		}
	}
	close_fd(fd);
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
	run_pipe(mini->next, *pid, *fd, *size);
	(*size)--;
}

void	run(t_mini *mini)
{
	pid_t	*pid;
	int		**fd;
	int		size;
	int		i;

	size = minisize(mini);
	if (mini->argv)
	{
		if (check_cmd(mini))
			ours_is_first(mini, &size, &fd, &pid);
		else
		{
			pid = malloc(sizeof(pid_t) * size);
			fd = fds_and_pipes_init(size);
			run_pipe(mini, pid, fd, size);
		}
		i = 0;
		while (i < size)
			waitpid(pid[i++], &g_status, 0);
		g_status /= 256;
		free_fd_pid(fd, pid);
	}
}

int	body(t_env *env)
{
	t_mini	*mini;
	char	*line;

	while (1)
	{
		line = readline("😎 \033[0;36m\033[1mminishell ▸ \033[0m");
		if (line[0] != '\0')
		{
			add_history(line);
			mini = new_mini(env, 0);
			if (check_line(line))
				continue ;
			if (ft_parse(line, mini))
			{
				free_mini(mini);
				g_status = 1;
				continue ;
			}
			run(mini);
		}
		free(line);
		if (mini->ret != -1)
			return (mini->ret);
		free_mini(mini);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	argc = 0;
	argv = 0;
	env = envp_to_list(envp);
	return (body(env));
}
