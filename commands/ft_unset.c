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

	after = (find_on_head(*envr, unset))->next;
	pre = finde_pre_on_head(*envr, unset);
	pre->next = after;
}
