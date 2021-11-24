/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:18:42 by cliza             #+#    #+#             */
/*   Updated: 2021/11/24 20:05:46 by vbackyet         ###   ########.fr       */
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
#define SUCCESS 0
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
char	*search_key(char *key, t_env *env);
t_mini	*new_mini(char *line, t_env *env);
int		here_doc(char *line);
void	ft_putstr_fd(char *s, int fd);
t_env *find_on_head(t_env *env, char *head);
void show_sorted_env(t_env *envr);
void print_pwd_and_old_pwd(t_env *envr);
void ft_unset(char *unset, t_env **envr);
int ft_export(t_env *export, t_env **envr, int flag);
t_env	*envp_to_list(char **envp);
void paste_env(t_env *export, t_env **envr);
t_mini	*new_mini(t_env *env);
int		print_redir_error(char **line);
void	free_arr(char ***arr);
void	print_mini(t_mini *mini);

#endif
