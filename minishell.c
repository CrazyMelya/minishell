/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:42:45 by cliza             #+#    #+#             */
/*   Updated: 2021/11/08 20:33:02 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *line)
{
	while (*line && *line != '|')
	{
		if (*line == '\"')
		{
			while (*line != '\"' && *line)
				line++;
		}
		if (*line == '\'')
		{
			while (*line != '\'' && *line)
				line++;
		}
		if (*line == '<' && *(line + 1) == '<')
			return (1);
		line++;
	}
	return (-1);
}

t_mini	*new_mini(char *line, char **envp)
{
	t_mini *mini;

	mini = malloc(sizeof(t_mini));
	mini->argc = 0;
	mini->argv = NULL;
	mini->write_file = NULL;
	mini->write_type = -1;
	mini->read_file = NULL;
	mini->envp = envp;
	mini->read_type = here_doc(line);
	mini->next = NULL;
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
			if (fd == -1)
		{
			printf("no such file or directory\n");
			exit(0);
		}
		dup2(fd, 1);
		close(fd);
	}
	if (mini->read_file)
	{
		fd = open(mini->read_file, O_RDONLY);
		if (fd == -1)
		{
			printf("no such file or directory\n");
			exit(0);
		}
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

	i = 0;
	if (mini->argv)
	{
		while (mini->argv[i])
		{
			ft_putstr_fd(mini->argv[i], 1);
			ft_putchar_fd(' ', 1);
			i++;
		}
	}
	ft_putstr_fd(mini->write_file, 1);
	if (mini->write_type == 1)
		ft_putstr_fd(" >> ", 1);
	else if (!mini->write_type)
		ft_putstr_fd(" > ", 1);
	ft_putstr_fd(mini->read_file, 1);
	if (mini->read_type == 1)
		ft_putstr_fd(" << ", 1);
	else if (!mini->read_type)
		ft_putstr_fd(" < ", 1);
	ft_putchar_fd('\n', 1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mini	*mini;
	t_mini	*temp;
	//pid_t	pid;
	int		i;
	
	argc = 0;
	argv = 0;
	while (1)
	{
		line = readline("😎 \033[0;36m\033[1mminishell ▸ \033[0m");
		add_history(line);
		if (ft_strncmp(line, "", 1))
		{
			mini = new_mini(line, envp);
			if (check_line(line))
				continue;
			if (ft_parse(line, mini))
				continue;
			//pid = fork();
			i = 0;
			temp = mini;
			while (temp)
			{
				print_mini(temp);
				temp = temp->next;
			}
			//if (!pid)
			//run_program(mini, envp);
			wait(0);
		}
		free(line);
	}
}