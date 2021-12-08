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

int	ft_cd(char *path, t_env *env)
{
	int		r;
	char	*full_path;

	if (path == NULL)
	{
		path = find_on_head(env, "HOME")->content;
	}
	r = chdir(path);
	full_path = ft_pwd_in();
	if (r == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
	}
	do_oldpwd(env);
	do_pwd(full_path, env);
	free(full_path);
	return(SUCCESS);
}
///^D ^C
// ◦ ctrl-C print a new prompt on a newline.
// ◦ ctrl-D exit the shell.
// ◦ ctrl-\ do nothing.