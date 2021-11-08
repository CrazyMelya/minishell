/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:18:42 by cliza             #+#    #+#             */
/*   Updated: 2021/11/08 20:10:24 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#define SPEC "<>$\'\" |"
#define SPEC2 "><| "
#define SPEC3 "<>\'\" |"
#define SYNT_ERR "bash: syntax error near unexpected token"

typedef	struct s_mini
{
	int				argc;
	char			**argv;
	char			**envp;
	char			*write_file;
	int				write_type;
	char			*read_file;
	int				read_type;
	struct s_mini	*next;
	
}				t_mini;

int 	ft_echo(int argc, char **argv);
int		check_line(char *line);
void	write_redir(t_mini *mini, char **line);
int		read_redir(t_mini *mini, char **line);
char	*ft_chrjoin(char *str, char c);
int		ft_parse(char *line, t_mini *mini);
char	**add_arg(int argc, char **argv, char *arg);
char	*search_key(char *key, char **envp);
t_mini	*new_mini(char *line, char **envp);

#endif
