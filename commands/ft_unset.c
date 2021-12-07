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

void	ft_unset(t_env **envr, char *unset)
{
	t_env	*after;
	t_env	*pre;

	after = find_on_head(*envr, unset);
	pre = finde_pre_on_head(*envr, unset);
	if (!(after) || !(pre))
		return ;
	free(pre->next->key);
	free(pre->next->content);
	free(pre->next->next);
	free(pre->next);	
	pre->next = after->next;
}
