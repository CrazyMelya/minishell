/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:18:42 by cliza             #+#    #+#             */
/*   Updated: 2021/12/03 22:06:33 by cliza            ###   ########.fr       */
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
#include <dirent.h>
#define SPEC "<>$\'\" |"
#define SPEC2 "<>| "
#define SPEC3 "<>\'\" |"
#define SYNT_ERR "bash: syntax error near unexpected token"

int g_status;

typedef struct s_env
{
	char			*key;
	char			*content;
	int				flag;
	struct s_env	*next;
}				t_env;

typedef struct s_redir
{
	char			*filename;
	int				type;
	struct s_redir	*next;
	
} 				t_redir;

typedef struct s_argv
{
	char			*arg;
	struct s_argv	*next;
}				t_argv;


typedef	struct s_mini
{
	int				argc;
	t_argv			*argv;
	t_env			*env;
	char			*write_file;
	int				write_type;
	t_redir			*read_redir;
	int				here_doc[2];
	struct s_mini	*next;
}				t_mini;

int 	ft_echo(int argc, char **argv);
int		check_line(char *line);
int		write_redir(t_mini *mini, char **line);
void	read_redir(t_mini *mini, char **line);
char	*ft_chrjoin(char *str, char c);
int		ft_parse(char *line, t_mini *mini);
void	add_arg(t_argv **argv, char *arg);
char	*search_key(char **key, t_env *env);
t_mini	*new_mini(t_env *env);
int		print_redir_error(char **line);
void	free_arr(char ***arr);
void	print_mini(t_mini *mini);
void	single_quotes(char **line, char **arg);
void	double_quotes(t_mini *mini, char **line, char **arg);
void	quotes(t_mini *mini, char **line, char **arg);
int		check_dir(char *filename);

#endif
