#include "../minishell.h"

t_env *turn_char_to_leaf(char *my_arg)
{
	t_env *export2 = (t_env*)malloc(sizeof(t_env));
	char **parts = ft_split(my_arg, '=');
	export2->key = parts[0];
	export2->content = parts[1];
	export2->next = NULL;
	export2->flag  = 0;
	free(parts);
	return(export2);
}


int ft_export(t_env **envr, char *flag)
{
	//Функция для того чтобы экспортировть перменные в переменную окружения - чужую - нашу - ненастоящую!!
	if (!flag)
	{
		// printf("here we go!\n");
		show_sorted_env(*envr);
		return(0);
	}
	else
	{		
	t_env *first_el = *envr;
	t_env *export2 = turn_char_to_leaf(flag);
	// export2 = (t_env*)malloc(sizeof(t_env));
	// export2->key = "lylyly";
	// export2->content = "bububub";
	// export2->next = NULL;
	// export2->flag  = 0;
	paste_env(export2, envr);
	*envr = first_el;
	// show_env(*envr);
	show_sorted_env(*envr);

	// sort_env(envr);
	free(export2);
	return(0);
	}
}
