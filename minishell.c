/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:42:45 by cliza             #+#    #+#             */
/*   Updated: 2021/12/04 15:42:13 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**argv_to_arr(t_argv *argv, int	argc)
{
	char	**result;
	int		i;

	result = malloc(sizeof(char *) * (argc + 1));
	i = 0;
	while (i < argc)
	{
		result[i] = argv->arg;
		i++;
		argv = argv->next;
	}
	result[i] = NULL;
	return(result);
}

void	free_arr(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
}

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
			content = ft_chrjoin(content, envp[i][j++]);
		add_env(&env, new_env(key, content));
		i++;
	}
	return (env);
}

int	detect_len_of_stack(t_env *env)
{
	int	i;

	i = 0;
	if (env == NULL)
		return (i);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	*ft_strjoin_env(char const *s1, char const *s2, char c)
{
	size_t	len;
	int		i;
	char	*kuda;

	i = 0;
	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	kuda = (char *)malloc(sizeof(char) * (len + 2));
	if (!kuda)
		return (NULL);
	while (*s1)
		kuda[i++] = *s1++;
	kuda[i++] = c;
	while (*s2)
		kuda[i++] = *s2++;
	kuda[i] = '\0';
	return (kuda);
}

char **envp_to_arr(t_env *envr)
{
	int t = 0;
	int i = detect_len_of_stack(envr);
	char **env_in_list = malloc(i * sizeof(char *));
	while(t < i)
	{
		
		env_in_list[t] = ft_strjoin_env(envr->key, envr->content, '=');
		envr = envr->next;
		t++;
	}
	env_in_list[t] = 0;
	return (env_in_list);
}

char	*search_path2(char **pathes, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (pathes[i])
	{
		path = ft_strjoin_env(pathes[i], cmd, '/');
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

char	*search_path(t_env *env, char *cmd)
{
	char	*sub_path;

	sub_path = NULL;
	while (env || !sub_path)
	{
		if (!ft_strncmp(env->key, "PATH", 5))
			sub_path = env->content;
		env = env->next;
	}
	return (search_path2(ft_split(sub_path + 5, ':'), cmd));
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
			ft_putstr_fd(": Permission denied\n", 2);
			exit(1);
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
	while (temp)
	{
		if (!temp->type)
		{
			if (check_dir(temp->filename))
				exit(1);
			if (access(temp->filename, F_OK))
			{
				ft_putstr_fd("😎 \033[0;36m\033[1mminishell ▸ \033[0m", 2);
				ft_putstr_fd(temp->filename, 2);
				ft_putstr_fd(": no such file or directory\n", 2);
				exit(1);
			}
			if (access(temp->filename, R_OK))
			{
				ft_putstr_fd("😎 \033[0;36m\033[1mminishell ▸ \033[0m", 2);
				ft_putstr_fd(temp->filename, 2);
				ft_putstr_fd(": Permission denied\n", 2);
				exit(1);
			}
			fd = open(temp->filename, O_RDONLY);
			close(fd);
		}
		temp = temp->next;
	}
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

int	check_dir(char *filename)
{
	void	*dir;
	
	dir = opendir(filename);
	if (dir)
	{
		closedir(dir);
		printf("😎 \033[0;36m\033[1mminishell ▸ \033[0m %s: is a directory\n", filename);
		return (-1);
	}
	else
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
			printf("😎 \033[0;36m\033[1mminishell ▸ \033[0m"
				"%s: command not found\n", mini->argv->arg);
			exit(127);
		}
	}
	else
		path = mini->argv->arg;
	if (execve(path, argv_to_arr(mini->argv, mini->argc), envp_to_arr(mini->env)))
	{
		printf("😎 \033[0;36m\033[1mminishell ▸ \033[0m"
			"%s: No such file or directory\n", mini->argv->arg);
		exit(127);
	}
}

int our_commands(t_mini *mini)
{
	if (!ft_strncmp(mini->argv->arg, "echo", 5))
	{
		ft_echo(mini->argc, argv_to_arr(mini->argv, mini->argc));
		exit(0);
	}
	else if (!ft_strncmp(mini->argv->arg, "cd", 3))
	{
		ft_cd(argv_to_arr(mini->argv, mini->argc)[1], mini->env);
		exit(0);
	}
	else if (!ft_strncmp(mini->argv->arg, "pwd", 4))
	{
		ft_pwd( mini->env);
		exit(0);
	}
	else if (!ft_strncmp(mini->argv->arg, "env", 4))
	{
		ft_env(mini->env);
		exit(0);
	}
	else if (!ft_strncmp(mini->argv->arg, "export", 7))
	{
		printf("here!!!\n");
		ft_export(&mini->env, argv_to_arr(mini->argv, mini->argc)[1]);
		exit(0);
	}	
	return(1);
}

void	ft_pipe(t_mini *mini, int **fds, int n, int size)
{
	int		i;

	redir_read(mini, fds, n, size);
	redir_write(mini, fds, n, size);
	i = 0;
	while (i < size)
	{
		close(fds[i][0]);
		close(fds[i++][1]);
	}
	if (our_commands(mini))
		other_cmd(mini);
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		free(env->key);
		free(env->content);
		temp = env->next;
		free(env);
		env = temp;
	}
}

void	free_redir(t_redir *redir)
{
	t_redir	*temp;

	while(redir)
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

	while(argv)
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

void	free_all(t_mini *mini, int **fd, pid_t *pid)
{
	int		i;

	free_mini(mini);
	i = 0;
	while (fd[i])
		free(fd[i++]);
	free(pid);
	free(fd);
}

int	**fds_and_pipes_init(int size)
{
	int	i;
	int	**fd;

	fd = malloc(sizeof(int *) * (size + 1));
	i = 0;
	while (i < size)
		fd[i++] = malloc(sizeof(int) * 2);
	fd[i] = NULL;
	i = 0;
	while (i < size)
		pipe(fd[i++]);
	return (fd);
}

void	run_pipe(t_mini *mini, pid_t *pid, int **fd, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		pid[i] = fork();
		if (!pid[i])
			ft_pipe(mini, fd, i, size);
		mini = mini->next;
		i++;
	}
	i = 0;
	while (i < size)
	{
		close(fd[i][0]);
		close(fd[i++][1]);
	}
}

void	run(t_mini *mini)
{
	pid_t	*pid;
	int		**fd;
	int		size;

	size = minisize(mini);
	pid = malloc(sizeof(pid_t) * size);
	fd = fds_and_pipes_init(size);
	run_pipe(mini, pid, fd, size);
	while (size--)
		waitpid(-1, &g_status, 0); 
	g_status /= 256;
	free_all(mini, fd, pid);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mini	*mini;
	t_env	*env;
	
	argc = 0;
	argv = 0;
	env = envp_to_list(envp);
	while (1)
	{
		line = readline("😎 \033[0;36m\033[1mminishell ▸ \033[0m");
		if (line[0] != '\0')
		{
			add_history(line);
			mini = new_mini(env);
			if (check_line(line))
				continue;
			if (ft_parse(line, mini))
			{
				free_mini(mini);
				g_status = 1;
				continue;
			}
			run(mini);
		}
		free(line);
	}
}
