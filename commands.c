//написание команд 
// ◦ echo with option -n
// ◦ cd with only a relative or absolute path(- или вообще без аргументов????? . .. absolut_path relative_path)
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define SUCCESS 0
// flag - есть -n или нет

typedef struct s_env
{
char *key;
char *content;
struct s_env *next;

}				t_env;



void ft_putstr_fd(char *str, int fd)
{
	while(*str)
	{
		write(fd, str, 1);
		str++;
	}

}


int ft_echo(char *str, int flag, int fd)
{
	ft_putstr_fd(str, fd);
	if (flag)
		ft_putstr_fd("\n", fd);
	return(SUCCESS);
}


int do_oldpwd(char *path, t_env *env)
{
// ret = chdir(env_path);
return(0);
}


int do_pwd(char *path, t_env *env)
{
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
	do_oldpwd(path, env);
	do_pwd(path, env);


	return(SUCCESS);
}

t_env	*insert_into_stack()
{
	t_env	*stack;
	t_env	*stack1;
	t_env	*first_el_of_stack;
	int		i;
	int		pos_index;

	pos_index = 0;
	stack = (t_env *)malloc(sizeof(t_env));
	stack1 = (t_env *)malloc(sizeof(t_env));
	stack->key = "PWD";
	stack-> content = "/Users/vbackyet/Desktop/moi_minishell/minishell";
	first_el_of_stack = stack;
	stack1->key = "OLDPWD";
	stack1->content = "/Users/vbackyet/Desktop/moi_minishell/minishell";
	stack-> next = stack1;
	return (first_el_of_stack);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;

	str = readline("bash$ ");
	t_env *envr;
	// ft_echo(str, 0 , 1);
	envr = insert_into_stack();
	int r = chdir("/Users/vbackyet/Desktop/moi_minishell/minishell/kuku");
	printf("(%d)\n",r);
	ft_cd(str, envr);

//что мне нужно - чтобы ты распрсил перменню окружения и все поместил с список структур 
	char *dir = getenv("PWD");
	printf("%s\n", dir);
	printf("%s\n", env[16]);
}






