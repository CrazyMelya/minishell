#include "../minishell.h"

t_env	*turn_char_to_leaf(char *my_arg)
{
	t_env	*export2;
	char	**parts;

	export2 = (t_env *)malloc(sizeof(t_env));
	parts = ft_split(my_arg, '=');
	export2->key = parts[0];
	export2->content = parts[1];
	export2->next = NULL;
	export2->flag = 0;
	free(parts);
	return (export2);
}

int	ft_export(t_env **envr, char *flag)
{
	t_env	*first_el;
	t_env	*export2;

	if (!flag)
	{
		show_sorted_env(*envr);
		return (0);
	}
	else
	{		
		first_el = *envr;
		export2 = turn_char_to_leaf(flag);
		paste_env(export2, envr);
		*envr = first_el;
		show_sorted_env(*envr);
		free(export2);
		return (0);
	}
}
