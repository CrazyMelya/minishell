/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:18:42 by cliza             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/07 16:20:40 by vbackyet         ###   ########.fr       */
=======
/*   Updated: 2021/11/09 19:21:34 by cliza            ###   ########.fr       */
>>>>>>> e9f03b8ab1a7a59cdba981094d9be00a1343fb4c
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
<<<<<<< HEAD
=======
#define SPEC "<>$\'\" |"
#define SPEC2 "><| "
#define SPEC3 "<>\'\" |"
#define SYNT_ERR "bash: syntax error near unexpected token"

typedef struct s_env
{
	char			*key;
	char			*content;
	int				flag;
	struct s_env	*next;
}				t_env;
>>>>>>> e9f03b8ab1a7a59cdba981094d9be00a1343fb4c

typedef	struct s_mini
{
	int				argc;
	char			**argv;
<<<<<<< HEAD
=======
	t_env			*env;
>>>>>>> e9f03b8ab1a7a59cdba981094d9be00a1343fb4c
	char			*write_file;
	int				write_type;
	char			*read_file;
	int				read_type;
	struct s_mini	*next;
	
}				t_mini;

<<<<<<< HEAD
// int ft_echo(int argc, char **argv);

#endif
=======
int 	ft_echo(int argc, char **argv);
int		check_line(char *line);
void	write_redir(t_mini *mini, char **line);
int		read_redir(t_mini *mini, char **line);
char	*ft_chrjoin(char *str, char c);
int		ft_parse(char *line, t_mini *mini);
char	**add_arg(int argc, char **argv, char *arg);
char	*search_key(char *key, t_env *env);
t_mini	*new_mini(char *line, t_env *env);
int		here_doc(char *line);

#endif
>>>>>>> e9f03b8ab1a7a59cdba981094d9be00a1343fb4c
