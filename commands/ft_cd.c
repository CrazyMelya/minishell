#include "../minishell.h"

t_env	*find_on_head(t_env *env, char *head)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, head) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*ft_pwd_in(void)
{
	char	*dir;

	dir = malloc(1024);
	getcwd(dir, 1024);
	return (dir);
}

int	do_pwd(char *path, t_env *env)
{
	t_env	*my_str;

	my_str = find_on_head(env, "PWD");
	my_str->content = path;
	return (0);
}

int	do_oldpwd(t_env *env)
{
	t_env	*my_str;

	my_str = find_on_head(env, "OLDPWD");
	free(my_str->content);
	my_str->content = find_on_head(env, "PWD")->content;
	return (0);
}


void	print_error2(char *error, char *str)
{
	ft_putstr_fd("😎 \033[0;36m\033[1mminishell ▸ \033[0m", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(error, 2);
}


int	ft_cd(char *path, t_env *env)
{
	int		r;
	char	*full_path;
	t_env	*head_of_home;

	if (path == NULL)
	{
		head_of_home = find_on_head(env, "HOME");
		if (head_of_home == NULL)
		{
			print_error(" : HOME not set", "cd");
			return (1);
		}
		path = head_of_home->content;
	}
	r = chdir(path);
	full_path = ft_pwd_in();
	if (r == -1)
		print_error2(": No such file or directory", path);
	do_oldpwd(env);
	do_pwd(full_path, env);
	free(full_path);
	return (SUCCESS);
}
///^D ^C
// ◦ ctrl-C print a new prompt on a newline.
// ◦ ctrl-D exit the shell.
// ◦ ctrl-\ do nothing.