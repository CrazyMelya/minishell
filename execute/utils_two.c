/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:31:37 by cliza             #+#    #+#             */
/*   Updated: 2021/12/05 06:33:45 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while (fd[i])
		pipe(fd[i++]);
	return (fd);
}

void	close_fd(int **fds)
{
	int	i;

	i = 0;
	while (fds[i])
	{
		close(fds[i][0]);
		close(fds[i++][1]);
	}
}

int	check_cmd(t_mini *mini)
{
	if (!ft_strncmp(mini->argv->arg, "echo", 5))
		return (1);
	else if (!ft_strncmp(mini->argv->arg, "cd", 3))
		return (1);
	else if (!ft_strncmp(mini->argv->arg, "pwd", 4))
		return (1);
	else if (!ft_strncmp(mini->argv->arg, "env", 4))
		return (1);
	else if (!ft_strncmp(mini->argv->arg, "export", 7))
		return (1);
	else if (!ft_strncmp(mini->argv->arg, "unset", 6))
		return (1);
	else if (!ft_strncmp(mini->argv->arg, "env", 4))
		return (1);
	else if (!ft_strncmp(mini->argv->arg, "exit", 5))
		return (1);
	return (0);
}
