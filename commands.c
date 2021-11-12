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

// ◦ unset with no options -
// ◦ env with no options or arguments - 
// ◦ exit with no options

// #include <readline/readline.h>
// #include <readline/history.h>
#include "readline/readline.h"
#include "readline/history.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"




// flag - есть -n или нет



void ft_putstr_fd(char *str, int fd)
{
	while(*str)
	{
		write(fd, str, 1);
		str++;
	}

}

//}




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




t_env *finde_pre_on_head(t_env *env, char *head)
{

	while (env->next != NULL)
	{
		// printf("-[[[[[[]]]]]] %s\n", env->key);
		if (ft_strcmp(env->next->key, head) == 0)
		{
			// printf("-[[[[[[%s]]]]]] \n", env->key);
			return(env);
		}
		// printf("+ %s\n", env->key);
		env = env->next;
		// printf("- %s\n", env->key);
	}
	printf("NO WAY %s\n", head);
	return(NULL);
}





void show_env(t_env *envr)
{
	listprint(envr);
}

void paste_env(t_env *export, t_env **envr)
{
	t_env *first_el = *envr;
	while ((*envr)->next != NULL)
	{
		*envr = (*envr)->next;
	}	

	(*envr)->next= export;

	// *envr  = export;
	*envr = first_el;
}

int	detect_len_of_stack(t_env *stack)
{
	int	i;

	i = 0;
	if (stack == NULL)
		return (0);
		// printf("%d\n", len_of_the_stack);
	// printf("hello world\n");
	while (stack->next != NULL)
	{
		i++;
		stack = stack-> next;
	}
	printf("hello world\n");
	return (i + 1);
}


int sum_of_lett(char *my_word, int to)
{
	int i = 0;
	int sum = 0;
	while((my_word[i] != '\0') && (i <= to))
	{
		sum+= (int)my_word[i];
		i++;
	}
	return(sum);
}



char *find_the_min(t_env *envr,int from, int i)
{
	char *the_word_of_min = NULL;
	int flag = 2;
	while (envr->next != NULL)
	{
		// printf("-----%d--%s--\n" ,envr->flag, envr->key);
		if (envr->flag)
			envr = envr->next;
		else{
			if (sum_of_lett(envr->key, i) <= from)
			{
				the_word_of_min = envr->key;
				from = sum_of_lett(envr->key, i);
				flag--;
			}
			// printf("  &&&&&&%d %d %s %d %d&&&&&\n",sum_of_lett(envr->key, i), i, envr->key, from , flag);
			// sleep(3);
			if ((sum_of_lett(envr->key, i) == from) && (flag < 0))
			{
				return(NULL);
			}
			envr = envr->next;
		}
	}
	// printf("-----%d--%s--\n" ,envr->flag, envr->key);
	if (!(envr->flag))
	{
		
		if (sum_of_lett(envr->key, i) <= from)
		{
			the_word_of_min = envr->key;
			from = sum_of_lett(envr->key, i);
			flag--;
		}
		if ((sum_of_lett(envr->key, i) == from) && (flag < 0))
			return(NULL);
		///
		
		if (the_word_of_min == NULL)
		 	the_word_of_min = envr->key;
		
	}
	// sleep(2);
	return(the_word_of_min);
}


void back_flags(t_env *env)
{
	while (env->next != NULL)
	{
		env->flag = 0;
		env = env->next;
		// printf("- %s\n", env->key);
	}
env->flag = 0;
}

void show_sorted_env(t_env *envr)
{
	int first_lett;
	char *the_min_word;
	int from;
	int len_of_the_stack = detect_len_of_stack(envr);
	int i = 0;
	from = (int)envr->key[0];
	printf("%d\n", len_of_the_stack);
	while(len_of_the_stack)
	{
		while((the_min_word =  find_the_min(envr,from, i)) == NULL)
		{

			// printf("***********%s********\n", the_min_word);
			i++;
			from = from + (int)envr->key[i];
		}
		// printf("%d\n", len_of_the_stack);
		i++;
		from = from + (int)envr->key[i];
		// printf("||%d %s||\n", from, the_min_word);

		t_env *the_el = find_on_head(envr, the_min_word);
		(*the_el).flag = 1;
		printf("%s %s\n", the_el->key, the_el->content);
		len_of_the_stack--;
	}
	back_flags(envr);

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
	stack->flag = 0;
	stack-> content = "/Users/vbackyet/Desktop/moi_minishell/minishell";
	first_el_of_stack = stack;
	stack1->key = "OLDPWD";
	stack1->content = "/Users/vbackyet/Desktop/moi_minishell/minishell";
	stack1->next  = NULL;
	stack1->flag  = 0;
	stack->next = stack1;

	return (first_el_of_stack);
}



void print_pwd_and_old_pwd(t_env *envr)
{
	printf( "PWD : %s\n"  ,find_on_head(envr, "PWD")->content);
	printf( "OLDPWD : %s\n"  ,find_on_head(envr, "OLDPWD")->content);

}

void ft_unset(char *unset, t_env **envr)
{
	// printf("MY ENV!!!\n");
	// show_env(*envr);
	// printf("\nMY ENV!!!\n");
	t_env *after = (find_on_head(*envr, unset))->next;//доделать!!!!!!
	t_env *pre = finde_pre_on_head(*envr, unset);
	pre->next = after;
}

char	*ft_strjoin_env(char const *s1, char const *s2)
{
	size_t	len;
	int		i;
	char	*kuda;

	i = 0;
	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	kuda = (char *)malloc(sizeof(char) * (len + 2));
	if (!kuda)
		return (NULL);
	while (*s1)
		kuda[i++] = *s1++;
	kuda[i++] = '=';
	while (*s2)
		kuda[i++] = *s2++;
	kuda[i] = '\0';
	return (kuda);
}


char **from_list_to_massive(t_env *envr)
{
	int t = 0;
	int i = detect_len_of_stack(envr);
	char **env_in_list =malloc(i*sizeof(char *));
	while(t < i)
	{
		
		env_in_list[t] = ft_strjoin_env(envr->key, envr->content);
		envr = envr->next;
		t++;
	}
	env_in_list[t] = 0;
	return (env_in_list);
}



// int	main(int argc, char **argv, char **env)
// {
// 	char	*str;

// 	str = readline("bash$ ");
// 	t_env *envr;
// 	t_env export;
// 	// ft_echo(str, 0 , 1);
// 	envr = insert_into_stack();
// 	// listprint(envr);
// 	// int r = chdir("/Users/vbackyet/Desktop/moi_minishell/minishell/kuku");
// 	// printf("(%d)\n",r);
// 	// print_pwd_and_old_pwd(envr);
// 	// ft_cd(str, envr);
	
// 	// ft_pwd();
// 	export.key = "ONE";
// 	export.content = "TWO bla bla bla";
// 	export.next = NULL;
// 	export.flag = 0;
// 	ft_export(&export,&envr,0);
	
// 	ft_export(&export,&envr,1);
// 	printf("+================================================\n");
// 	ft_unset("lylyly",&envr);
// 	ft_export(&export,&envr,1);
// 	// envr = envp_to_list(env);
// 	// char **listik = from_list_to_massive(envr);
// 	// printf("[[%s]]\n", listik[0] );

// 	// ft_unset();
// //что мне нужно - чтобы ты распрсил перменню окружения и все поместил с список структур 
// 	// char *dir = getenv("PWD");
// 	// printf("getcwd:  (%s)\n", ft_pwd());
// 	// print_pwd_and_old_pwd(envr);
// }


// env | grep PATH



