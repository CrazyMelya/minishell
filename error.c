/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:10:01 by vbackyet          #+#    #+#             */
/*   Updated: 2021/12/09 19:10:04 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error2(char *error, char *str)
{
	ft_putstr_fd("😎 \033[0;36m\033[1mminishell ▸ \033[0m", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(error, 2);
}
