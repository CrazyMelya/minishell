/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:08:02 by cliza             #+#    #+#             */
/*   Updated: 2021/11/08 20:11:45 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_arg(int argc, char **argv, char *arg)
{
	char	**new_argv;
	int		i;

	if (!argc)
	{
		new_argv = malloc(sizeof(char *) * 2);
		new_argv[0] = arg;
		new_argv[1] = NULL;
	}
	else
	{
		new_argv = malloc(sizeof(char *) * (argc + 2));
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

char	*search_key(char *key, char **envp)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		result = NULL;
		j = 0;
		while (envp[i][j] != '=')
		{
			result = ft_chrjoin(result, envp[i][j]);
			j++;
		}
		if (!ft_strncmp(key, result, ft_strlen(key) + 1))
		{
			free(result);
			result = ft_strchr(envp[i], '=');
			result++;
			return (result);
		}
		i++;
		free(result);
	}
	return (NULL);
}
