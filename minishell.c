/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:42:45 by cliza             #+#    #+#             */
/*   Updated: 2021/11/03 02:30:14 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_arg(char **argv, char *arg)
{
	char	**new_argv;
	int		i;

	i = 0;
	if (!argv)
	{
		new_argv = malloc(sizeof(char*) * 2);
		new_argv[0] = arg;
		new_argv[1] = NULL;
	}
	else
	{
		while (argv[i])
			i++;
		new_argv = malloc(sizeof(char*) * (i + 2));
		i = -1;
		while (argv[++i])
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
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = c;
	new[i] = 0;
	free(str);
	return (new);
}

void	new_redir(t_redir **redir, char *filename, int type)
{
	t_redir	*temp;

	if (*redir == NULL)
	{
		*redir = malloc(sizeof(t_redir));
		(*redir)->filename = filename;
		(*redir)->type = type;
	}
	else
	{
		temp = *redir;
		while (temp->next)
			temp = temp->next;
		temp->next = malloc(sizeof(t_redir));
		temp->next->filename = filename;
		temp->next->type = type;
	}
}

void	add_redir(t_mini *mini, char *line, int *i)
{
	char	*filename;
	int		type;
	
	(*i)++;
	if (line[*i] == '>')
	{
		type = 1;
		(*i)++;
	}
	else
		type = 0;
	filename = malloc(1);
	filename[0] = 0;
	while (line[*i] == ' ')
		(*i)++;
	while (line[*i] != ' ' && line[*i])
	{
		filename = ft_chrjoin(filename, line[*i]);
		(*i)++;
	}
	new_redir(&mini->redir, filename, type);
}

void	ft_parse(char *line, t_mini *mini)
{
	int	i;
	char *arg;

	i = 0;
	while (line[i])
	{
		arg = malloc(1);
		arg[0] = 0;
		while (line[i] == ' ')
			i++;
		while (line[i] != ' ' && line[i] && line[i] != '>')
		{
			arg = ft_chrjoin(arg, line[i]);
			i++;
		}
		if (line[i] == '>')
			add_redir(mini, line, &i);
		mini->argv = add_arg(mini->argv, arg);
		i++;
	}
}

int	main()
{
	char	*line;
	t_mini	*mini;
	t_redir	*temp;
	int		fd;
	int		stdout_cpy;
	
	mini = malloc(sizeof(t_mini));
	while (1)
	{
		mini->argv = NULL;
		mini->redir = NULL;
		line = readline("😎 \033[0;36m\033[1mminishell ▸ \033[0m");
		if (ft_strncmp(line, "", 1))
		{
			add_history(line);
			ft_parse(line, mini);
			if (mini->redir)
			{
				temp = mini->redir;
				while (temp)
				{
					if (temp->type)
						fd = open(temp->filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
					else
						fd = open(temp->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
					temp = temp->next;
					stdout_cpy = dup(1);
					dup2(fd, 1);
					close(fd);
					ft_echo(mini->argv);
					dup2(stdout_cpy, 1);
					close(stdout_cpy);
				}
			}
			else
				ft_echo(mini->argv);
			ft_putstr_fd("puk-puk\n", 1);
		}
		free(line);
	}
}
