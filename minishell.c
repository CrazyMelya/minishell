/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:42:45 by cliza             #+#    #+#             */
/*   Updated: 2021/11/11 21:45:24 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status = 0;

t_mini	*new_mini(t_env *env)
{
	t_mini *mini;

	mini = malloc(sizeof(t_mini));
	mini->argc = 0;
	mini->argv = NULL;
	mini->write_file = NULL;
	mini->write_type = -1;
	mini->env = env;
	mini->next = NULL;
	mini->read_redir = NULL;
	mini->here_doc[0] = -1;
	return (mini);
}

void	free_arr(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
}

t_env	*new_env(char *key, char *content)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	new->key = key;
	new->content = content;
	new->flag = 0;
	new->next = NULL;
	return (new);
}

void	add_env(t_env **env, t_env *new)
{
	t_env *temp;

	if (!(*env))
		*env = new;
	else
	{
		temp = *env;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

t_env	*envp_to_list(char **envp)
{
	int		i;
	t_env 	*env;
	char	*content;
	char	*key;
	int		j;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		key = NULL;
		j = 0;
		while (envp[i][j] != '=')
		{
			key = ft_chrjoin(key, envp[i][j]);
			j++;
		}
		content = NULL;
		j++;
		while (envp[i][j])
		{
			content = ft_chrjoin(content, envp[i][j]);
			j++;
		}
		add_env(&env, new_env(key, content));
		i++;
	}
	return (env);
}

char	*search_path(char **envp, char *cmd)
{
	char	**pathes;
	char	*path;
	char	*sub_path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			sub_path = envp[i];
		i++;
	}
	pathes = ft_split(sub_path + 5, ':');
	i = 0;
	while (pathes[i])
	{
		sub_path = ft_strjoin(pathes[i], "/");
		path = ft_strjoin(sub_path, cmd);
		free(sub_path);
		if (!access(path, X_OK))
		{
			free_arr(&pathes);
			return (path);
		}
		free(path);
		i++;
	}
	free_arr(&pathes);
	return (NULL);
}

void	run_program(t_mini *mini, int **fd, int n, int size, char **envp)
{
	char	*path;
	char	*line;
	int		fds;
	t_redir	*temp;
	int		i;

	temp = mini->read_redir;
	while (temp)
	{
		if (temp->type)
		{
			if (mini->here_doc[0] != -1)
				close(mini->here_doc[0]);
			pipe(mini->here_doc);
			line = readline("> ");
			while (ft_strncmp(line , temp->filename, ft_strlen(line) + 1))
			{
				ft_putendl_fd(line, mini->here_doc[1]);
				free(line);
				line = readline("> ");
			}
			close(mini->here_doc[1]);
		}
		temp = temp->next;
	}
	temp = mini->read_redir;
	if (temp)
	{
		while (temp)
		{
			if (!temp->type)
			{
				fds = open(temp->filename, O_RDONLY);
				if (fds == -1)
				{
					ft_putstr_fd("😎 \033[0;36m\033[1mminishell ▸ \033[0m", 2);
					ft_putstr_fd(temp->filename, 2);
					ft_putstr_fd(": no such file or directory\n", 2);
					exit(-1);
				}
				close(fds);
			}
			temp = temp->next;
		}
		temp = mini->read_redir;
		while (temp->next)
			temp = temp->next;
		if (temp->type)
			fds = mini->here_doc[0];
		else
		{
			if (mini->here_doc[0] != -1)
				close(mini->here_doc[0]);
			fds = open(temp->filename, O_RDONLY);
		}
		dup2(fds, 0);
		close(fds);
	}
	else if (size != 1 && n)
		dup2(fd[n - 1][0], 0);
	if (mini->write_file)
	{
		if (mini->write_type)
			fds = open(mini->write_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			fds = open(mini->write_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fds == -1)
		{
			ft_putstr_fd("😎 \033[0;36m\033[1mminishell ▸ \033[0m", 2);
			ft_putstr_fd(mini->write_file, 2);
			ft_putstr_fd(": no such file or directory\n", 2);
			exit(0);
		}
		dup2(fds, 1);
		close(fds);
	}
	else if (size != 1 && n != size - 1)
		dup2(fd[n][1], 1);
	i = 0;
	while (i < size)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	if (!ft_strncmp(mini->argv[0], "echo", 5))
	{
		ft_echo(mini->argc, mini->argv);
		exit(0);
	}
	else
	{
		if (mini->argv[0][0] != '.')
			path = search_path(envp, mini->argv[0]);
		else
			path = mini->argv[0];
		if (execve(path, mini->argv, envp))
		{
			ft_putstr_fd("😎 \033[0;36m\033[1mminishell ▸ \033[0m", 2);
			ft_putstr_fd(mini->argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(0);
		}
	}
}

int	minisize(t_mini	*mini)
{
	int	i;
	
	i = 1;
	while (mini->next)
	{
		mini = mini->next;
		i++;
	}
	return (i);
}

void	print_mini(t_mini *mini)
{
	int	i;
	t_redir	*temp;

	i = 0;
	if (mini->argv)
	{
		while (mini->argv[i])
		{
			printf("%s ", mini->argv[i]);
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
	while(temp)
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

void	redir_write(t_mini *mini, int **fds, int n, int size)
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
			ft_putstr_fd("😎 \033[0;36m\033[1mminishell ▸ \033[0m", 2);
			ft_putstr_fd(mini->write_file, 2);
			ft_putstr_fd(": no such file or directory\n", 2);
			exit(0);
		}
		dup2(fd, 1);
		close(fd);
	}
	else if (size > 1 && n != size - 1)
		dup2(fds[n][1], 1);
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
			while (ft_strncmp(line , temp->filename, ft_strlen(line) + 1))
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

void	read_file(t_mini *mini)
{
	t_redir	*temp;
	int		fd;

	temp = mini->read_redir;
	if (!temp->type)
	{
		fd = open(temp->filename, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("😎 \033[0;36m\033[1mminishell ▸ \033[0m", 2);
			ft_putstr_fd(temp->filename, 2);
			ft_putstr_fd(": no such file or directory\n", 2);
			exit(-1);
		}
		close(fd);
	}
	temp = temp->next;
}

void	redir_read(t_mini *mini, int **fds, int n, int size)
{
	int		fd;
	t_redir	*temp;

	if (mini->read_redir)
	{
		here_doc(mini);
		read_file(mini);
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
	else if (size > 1 && n)
		dup2(fds[n - 1][0], 0);
}

void	ft_pipe(t_mini *mini, int **fds, int n, int size, char **envp)
{
	int		i;
	char	*path;

	redir_read(mini, fds, n, size);
	redir_write(mini, fds, n, size);
	i = 0;
	while (i < size)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
	if (!ft_strncmp(mini->argv[0], "echo", 5))
	{
		ft_echo(mini->argc, mini->argv);
		exit(0);
	}
	else
	{
		if (mini->argv[0][0] != '.')
			path = search_path(envp, mini->argv[0]);
		else
			path = mini->argv[0];
		
		if (execve(path, mini->argv, envp))
		{
			ft_putstr_fd("😎 \033[0;36m\033[1mminishell ▸ \033[0m", 2);
			ft_putstr_fd(mini->argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(0);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mini	*mini;
	t_mini	*temp;
	t_env	*env;
	int		**fd;
	pid_t	*pid;
	int		size;
	int		i;
	
	argc = 0;
	argv = 0;
	env = envp_to_list(envp);
	while (1)
	{
		line = readline("😎 \033[0;36m\033[1mminishell ▸ \033[0m");
		if (ft_strncmp(line, "", 1))
		{
			add_history(line);
			mini = new_mini(env);
			if (check_line(line))
				continue;
			if (ft_parse(line, mini))
				continue;
			temp = mini;
			size = minisize(mini);
			pid = malloc(sizeof(pid_t) * size);
			i = 0;
			fd = malloc(sizeof(int *) * size);
			while (i < size)
				fd[i++] = malloc(sizeof(int) * 2);
			fd[i] = NULL;
			i = 0;
			while (i < size)
				pipe(fd[i++]);
			i = 0;
			while (i < size)
			{
				pid[i] = fork();
				if (!pid[i])
					ft_pipe(temp, fd, i, size, envp);
				temp = temp->next;
				i++;
			}
			// while (temp)
			// {
			// 	print_mini(temp);
			// 	temp = temp->next;
			// }
			// if (!pid)
			// 	run_program(mini, envp);
			// i = 0;
			// while (i < size)
			// {
			// 	waitpid(-1, &status, 0);
			// 	i++;
			// }
			i = 0;
			while (i < size)
			{
				waitpid(0, &status, 0);
				i++;
			// 	ft_putendl_fd("puk-puk", 1);
			}
		}
		free(line);
	}
}
