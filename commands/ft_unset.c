#include "../minishell.h"


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

void ft_unset( t_env **envr, char *unset)
{
	// printf("MY ENV!!!\n");
	// show_env(*envr);
	// printf("\nMY ENV!!!\n");
	t_env *after = (find_on_head(*envr, unset))->next;//доделать!!!!!!
	t_env *pre = finde_pre_on_head(*envr, unset);
	pre->next = after;
}
