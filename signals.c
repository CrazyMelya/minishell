/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:59:05 by vbackyet          #+#    #+#             */
/*   Updated: 2021/12/10 16:59:05 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define STDERR 2

static void	signal_cmd_ctrl_c(int sig)
{
	write(1, "\n", 1);
	(void)sig;
	signal(SIGINT, SIG_IGN);
}

static void	signal_ctrl_slash(int sig)
{
	(void)sig;
	ft_putendl_fd("Quit: 3", 2);
	signal(SIGINT, SIG_IGN);
}

void	signals_in_cmd(void)
{
	signal(SIGINT, signal_cmd_ctrl_c);
	signal(SIGQUIT, signal_ctrl_slash);
}

static void	signal_ctrl_c(int sig)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	signals_in_main(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_ctrl_c);
}
