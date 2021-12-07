#include "../minishell.h"

t_env *find_on_head(t_env *env, char *head)
{

	while (env->next != NULL)
	{
		if (ft_strcmp(env->key, head) == 0)
			return(env);
		// printf("+ %s\n", env->key);
		env = env->next;
		// printf("- %s\n", env->key);
	}
	if (ft_strcmp(env->key, head) == 0)
		return(env);
		// printf("+ %s\n", env->key);
	env = env->next;
	printf("NO WAY %s\n", head);
	return(NULL);
}



char *ft_pwd_in()
{
	char *dir;
	dir = malloc(1024);
	getcwd(dir, 1024);
	return dir;
	//или просто распечатать?
}

int do_pwd(char *path, t_env *env)
{
	//Заменяем текущий путь
	t_env *my_str = find_on_head(env, "PWD");
	my_str->content = path;
	return(0);
}

int do_oldpwd(t_env *env)
{
	t_env *my_str = find_on_head(env, "OLDPWD");

	my_str->content = find_on_head(env, "PWD")->content;
	//Заменяем старый путь
// ret = chdir(env_path);
	return(0);
}





int ft_cd(char *path, t_env *env)
{
	// функция меняет путь pwd и oldpwd
	//для того, чтобы функция меняла нужен лист формата - неважно какого формата есть структура head и content
	//проверка на существование этого пути
	// замена предыдущего на настоящий
	// замена настоящего на предстоящий

	// 1) просто путь



	int r = chdir(path);
	char *full_path = ft_pwd_in();
	if (path == NULL)
	{
		
	}
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