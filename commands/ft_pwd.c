/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:52:40 by vbackyet          #+#    #+#             */
/*   Updated: 2021/12/09 17:52:41 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
		ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}
