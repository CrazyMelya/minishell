/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:42:45 by cliza             #+#    #+#             */
/*   Updated: 2021/11/02 20:30:21 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_parse(char *line, t_mini *mini)
{
	int	i;
	char *value;

	i = 0;
	while (line[i])
	{
		value = malloc(1);
		value[0] = 0;
		while (line[i] == ' ')
			i++;
		while (line[i] != ' ' && line[i])
		{
			if (line[i] == '>')
			{
				mini->red = 1;
				if (line[i + 1] == '>')
					mini->red = 2;
			}
			else
				value = ft_chrjoin(value, line[i]);
			i++;
		}
		ft_lstadd_back(&mini->arg, ft_lstnew(value));
		i++;
	}
}

int	main()
{
	char	*line;
	t_mini	*mini;
	t_list	*temp;
	int		fd;
	
	mini = malloc(sizeof(t_mini));
	while (1)
	{
		mini->arg = NULL;
		mini->red = 0;
		line = readline("😎 \033[0;36m\033[1mminishell ▸ \033[0m");
		if (ft_strncmp(line, "", 1))
			add_history(line);
		ft_parse(line, mini);
		temp = mini->arg;
		fd = 1;
		if (mini->red == 1)
			fd = open(ft_lstlast(mini->arg)->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (mini->red == 2)
			fd = open(ft_lstlast(mini->arg)->content, O_WRONLY | O_CREAT | O_APPEND, 0666);
		ft_echo(mini, 1, fd);
		ft_lstclear(&mini->arg, free);
	}
}
