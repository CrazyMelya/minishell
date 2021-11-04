/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:42:45 by cliza             #+#    #+#             */
/*   Updated: 2021/11/04 13:36:39 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**add_arg(int argc, char **argv, char *arg)
{
	char	**new_argv;
	int		i;

	if (!argc)
	{
		new_argv = malloc(sizeof(char*) * 2);
		new_argv[0] = arg;
		new_argv[1] = NULL;
	}
	else
	{
		new_argv = malloc(sizeof(char*) * (argc + 2));
		i = -1;
		while (++i < argc)
			new_argv[i] = argv[i];
		new_argv[i++] = arg;
		new_argv[i] = NULL;
		free(argv);
	}
	return (new_argv);
}

char	*ft_chrjoin(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(ft_strlen(str) + 2);
	if (str)
	{
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	}
	new[i++] = c;
	new[i] = 0;
	free(str);
	return (new);
}

void	new_write_redir(t_mini *mini, char *filename, int type)
{
	int	fd;
	
	if (mini->write_file)
	{
		if (mini->write_type)
			fd = open(mini->write_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			fd = open(mini->write_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
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
}

int	here_doc(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
			return (1);
		i++;
	}
	return (-1);
}

void	new_read_redir(t_mini *mini, char *filename)
{
	int fd;

	if (mini->read_file)
	{
		if (!mini->read_type)
		{
			fd = open(mini->read_file, O_RDONLY);
			if (fd == -1)
			{
				ft_putendl_fd("No such file or directory", 2);
				exit(0);
			}
			close(fd);
		}
		free(mini->read_file);
		mini->read_file = filename;
	}
	else
	{
		if (mini->read_type == -1)
		{
			mini->read_file = filename;
			mini->read_type = 0;
		}
	}
}

void	read_redir(t_mini *mini, char *line, int *i)
{
	char	*filename;
	
	filename = NULL;
	(*i)++;
	if (line[*i] == '<')
		(*i)++;
	while (line[*i] == ' ')
		(*i)++;
	while (line[*i] != ' ' && line[*i])
	{
		filename = ft_chrjoin(filename, line[*i]);
		(*i)++;
	}
	new_read_redir(mini, filename);
}

void	write_redir(t_mini *mini, char *line, int *i)
{
	char	*filename;
	int		type;
	
	filename = NULL;
	(*i)++;
	if (line[*i] == '>')
	{
		type = 1;
		(*i)++;
	}
	else
		type = 0;
	while (line[*i] == ' ')
		(*i)++;
	while (line[*i] != ' ' && line[*i])
	{
		filename = ft_chrjoin(filename, line[*i]);
		(*i)++;
	}
	new_write_redir(mini, filename, type);
}

void	ft_parse(char *line, t_mini *mini)
{
	int	i;
	char *arg;

	i = 0;
	while (line[i])
	{
		arg = NULL;
		while (line[i] == ' ')
			i++;
		while (line[i] != ' ' && line[i] && line[i] != '>' && line[i] != '<')
		{
			arg = ft_chrjoin(arg, line[i]);
			i++;
		}
		if (arg)
		{
			mini->argv = add_arg(mini->argc, mini->argv, arg);
			mini->argc++;
		}
		if (line[i] == '>')
			write_redir(mini, line, &i);
		else if (line[i] == '<')
			read_redir(mini, line, &i);
		i++;
	}
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

void	run_program(t_mini *mini, char **envp)
{
	char	*path;
	int		fd;

	if (mini->write_file)
	{
		if (mini->write_type)
			fd = open(mini->write_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			fd = open(mini->write_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		dup2(fd, 1);
		close(fd);
	}
	if (mini->read_file)
	{
		fd = open(mini->read_file, O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	if (!ft_strncmp(mini->argv[0], "echo", 5))
	{
		ft_echo(mini->argc, mini->argv);
		exit(0);
	}
	else
	{
		path = search_path(envp, mini->argv[0]);
		if (execve(path, mini->argv, envp))
		{
			ft_putstr_fd("😎 \033[0;36m\033[1mminishell: \033[0m", 2);
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
	int		stdout_cpy;
	int		stdin_cpy;
	pid_t	pid;
	
	argc = 0;
	argv = 0;
	mini = malloc(sizeof(t_mini));
	while (1)
	{
		mini->argc = 0;
		mini->argv = NULL;
		mini->write_file = NULL;
		mini->write_type = -1;
		mini->read_file = NULL;
		line = readline("😎 \033[0;36m\033[1mminishell ▸ \033[0m");
		mini->read_type = here_doc(line);
		if (ft_strncmp(line, "", 1))
		{
			add_history(line);
			ft_parse(line, mini);
			stdout_cpy = dup(1);
			stdin_cpy = dup(0);
			pid = fork();
			if (!pid)
				run_program(mini, envp);
			wait(0);
			dup2(stdout_cpy, 1);
			close(stdout_cpy);
			dup2(stdin_cpy, 0);
			close(stdin_cpy);
		}
		free(line);
	}
}
