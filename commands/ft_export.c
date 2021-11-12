#include "../minishell.h"

int ft_export(t_env *export, t_env **envr, int flag)
{
	//Функция для того чтобы экспортировть перменные в переменную окружения - чужую - нашу - ненастоящую!!
	if (flag)
	{
		show_sorted_env(*envr);
		return(0);
	}
	else{
	t_env *first_el = *envr;
	t_env *export2;
	export2 = (t_env*)malloc(sizeof(t_env));
	export2->key = "lylyly";
	export2->content = "bububub";
	export2->next = NULL;
	export2->flag  = 0;
	paste_env(export, envr);
	paste_env(export2, envr);
	*envr = first_el;
	// show_env(*envr);
	show_sorted_env(*envr);

	// sort_env(envr);
	
	return(0);}
}
