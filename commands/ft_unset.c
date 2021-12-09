#include "../minishell.h"

t_env	*finde_pre_on_head(t_env *env, char *head)
{
	while (env->next != NULL)
	{
		if (ft_strcmp(env->next->key, head) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	ft_unset(t_env **envr, char *unset)
{
	t_env	*current;
	t_env	*pre;


	current = find_on_head(*envr, unset);
	pre = finde_pre_on_head(*envr, unset);
	if (!(current) || !(pre))
		return (1);
	pre->next = current->next;
	free(current->key);
	free(current->content);
	free(current);
	return (0);	
}
