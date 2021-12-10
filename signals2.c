/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:57:19 by vbackyet          #+#    #+#             */
/*   Updated: 2021/12/10 16:57:20 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_prompt(int sig)
{
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	myint(void)
{
	restore_prompt(0);
}

void	myint2(void)
{
	rl_redisplay();
}

void	myint3(void)
{
	printf("exit\n");
	exit(1);
}
