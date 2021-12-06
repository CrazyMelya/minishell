/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:24:10 by cliza             #+#    #+#             */
/*   Updated: 2021/12/05 06:27:11 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dir(char *filename)
{
	void	*dir;

	dir = opendir(filename);
	if (dir)
	{
		closedir(dir);
		print_error(": is a directory", filename);
		return (-1);
	}
	else
		return (0);
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
	while (env)
	{
		if (!ft_strncmp(env->key, "PATH", 5))
		{
			sub_path = env->content;
			break ;
		}
		env = env->next;
	}
	if (!sub_path)
		return (NULL);
	return (search_path2(ft_split(sub_path + 5, ':'), cmd));
}

void	print_error(char *error, char *str)
{
	ft_putstr_fd("😎 \033[0;36m\033[1mminishell ▸ \033[0m", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(error, 2);
}
