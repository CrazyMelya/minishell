/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliza <cliza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:18:42 by cliza             #+#    #+#             */
/*   Updated: 2021/12/09 21:26:41 by cliza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <sys/types.h>
#define SUCCESS 0
#define SPEC "<>$\'\" |="
#define SPEC2 "<>| "
#define SPEC3 "<>\'\" |"
#define SYNT_ERR "bash: syntax error near unexpected token"

int	g_status;

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
	int				ret;
	int				id;
	struct s_mini	*next;
}				t_mini;

//parser//

//commands//
t_env		*find_on_head(t_env *env, char *head);
void		show_sorted_env(t_env *envr);
int			ft_unset(t_env **envr, char *unset);
int			ft_export(t_env **envr, char *flag);
void		paste_env(t_env *export, t_env **envr);
int			ft_strcmp(char *s1, char *s2);
int			ft_cd(char *path, t_env *env);
int			ft_pwd(t_env *env);
void		listprint(t_env *env);
int			ft_env(t_env *env);
int		ft_exit(t_mini *mini, char **array);
int			ft_echo(int argc, char **argv);



int		check_line(char *line);
int		write_redir(t_mini *mini, char **line);
void	read_redir(t_mini *mini, char **line);
char	*ft_chrjoin(char *str, char c);
int		ft_parse(char *line, t_mini *mini);
void	add_arg(t_argv **argv, char *arg);
char	*search_key(char **key, t_env *env);
void	ft_putstr_fd(char *s, int fd);

t_env	*envp_to_list(char **envp);

t_mini	*new_mini(t_env *env, int id);
int		print_redir_error(char **line);
void	free_arr(char ***arr);
void	print_mini(t_mini *mini);
void	single_quotes(char **line, char **arg);
void	double_quotes(t_mini *mini, char **line, char **arg);
void	quotes(t_mini *mini, char **line, char **arg);
int		check_dir(char *filename);
char	*ft_strjoin_env(char const *s1, char const *s2, char c);

// error functions //
void		print_error2(char *error, char *str);
void		print_error(char *error, char *str);

// free functions //
void		free_arr(char ***arr);
void		free_mini(t_mini *mini);
void		free_argv(t_argv *argv);
void		free_redir(t_redir *redir);
void		free_fd_pid(int **fd, pid_t *pid);


int		redir_write(t_mini *mini, int **fds, int n, int size);
void	here_doc(t_mini *mini);
int		read_file(t_mini *mini);
int		redir_read(t_mini *mini, int **fds, int n, int size);

char	*search_path(t_env *env, char *cmd);
char	**argv_to_arr(t_argv *argv, int argc);

char	**envp_arr(t_env *envr);
t_env	*envp_to_list(char **envp);

int		check_cmd(t_mini *mini);
void	close_fd(int **fds);
int		**fds_and_pipes_init(int size);

int	minisize(t_mini	*mini);

// signal functions //
void 		rl_replace_line(const char *buffer, int val);
// void		myint(int);
// void		myint2(int);
void		myint3();

void	signals_in_main(void);
void	signals_in_cmd(void);

#endif
