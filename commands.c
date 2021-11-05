//написание команд 
// ◦ echo with option -n - 
// ◦ cd with only a relative or absolute path(- или вообще без аргументов????? . .. absolut_path relative_path)

// если такого не существует 
// если нет аргументов
// если две точки

// ◦ pwd with no options - 
// ◦ export with no options 

// нужно отсортирвать
// добавить новый
// вывести bash отсортированный
// если просто - то вывести список - отсортированный

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

char *ft_pwd()
{
	char *dir;
	dir = malloc(1024);
	getcwd(dir, 1024);
	return dir;
	//или просто распечатать?
}

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



void listprint(t_env *env)
{
	while (env->next != NULL)
	{
		printf("%s %s\n", env->key, env->content);
		env = env->next;
	}	
	printf("%s %s\n", env->key, env->content);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	// printf("|%s %s|",s1, s2 );
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}


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


int do_oldpwd(t_env *env)
{
	t_env *my_str = find_on_head(env, "OLDPWD");

	my_str->content = find_on_head(env, "PWD")->content;
	//Заменяем старый путь
// ret = chdir(env_path);
	return(0);
}


int do_pwd(char *path, t_env *env)
{
	//Заменяем текущий путь
	t_env *my_str = find_on_head(env, "PWD");
	my_str->content = path;
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
	char *full_path = ft_pwd();
	do_oldpwd(env);
	
	do_pwd(full_path, env);
	return(SUCCESS);
}



void show_env(t_env *envr)
{
	listprint(envr);
}

void paste_env(t_env *export, t_env **envr)
{
	while ((*envr)->next != NULL)
	{
		// printf("%s %s\n", env->key, env->content);
		*envr = (*envr)->next;
	}	
	*envr = (*envr)->next;
	*envr  = export;
}



int ft_export(t_env *export, t_env **envr, int flag)
{
	//Функция для того чтобы экспортировть перменные в переменную окружения - чужую - нашу - ненастоящую!!
	if (flag)
		show_env(*envr);
	t_env *first_el = *envr;
	paste_env(export, envr);
	printf("!!!!!]]]]\n\n\n");
	*envr = first_el;
	show_env(*envr);
	printf("!!!!!]]]]\n\n\n");
	// sort_env(envr);
	
	return(0);
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
	stack1->next  = NULL;
	stack->next = stack1;

	return (first_el_of_stack);
}



void print_pwd_and_old_pwd(t_env *envr)
{
	printf( "PWD : %s\n"  ,find_on_head(envr, "PWD")->content);
	printf( "OLDPWD : %s\n"  ,find_on_head(envr, "OLDPWD")->content);

}



int	main(int argc, char **argv, char **env)
{
	char	*str;

	str = readline("bash$ ");
	t_env *envr;
	t_env export;
	// ft_echo(str, 0 , 1);
	envr = insert_into_stack();
	// listprint(envr);
	// int r = chdir("/Users/vbackyet/Desktop/moi_minishell/minishell/kuku");
	// printf("(%d)\n",r);
	// print_pwd_and_old_pwd(envr);
	// ft_cd(str, envr);
	
	// ft_pwd();
	export.key = "ONE";
	export.content = "TWO bla bla bla";
	export.next = NULL;
	ft_export(&export,&envr,0);

//что мне нужно - чтобы ты распрсил перменню окружения и все поместил с список структур 
	char *dir = getenv("PWD");
	printf("getcwd:  (%s)\n", ft_pwd());
	// print_pwd_and_old_pwd(envr);
}


// env | grep PATH



