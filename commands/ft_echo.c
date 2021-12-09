/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:51:59 by vbackyet          #+#    #+#             */
/*   Updated: 2021/12/09 17:51:59 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(int argc, char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (argc > 1)
	{
		while (argv[i] && !ft_strncmp(argv[i], "-n", 3))
		{
			flag = 1;
			i++;
		}
		while (argv[i])
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1])
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	return (SUCCESS);
}
