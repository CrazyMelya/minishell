/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:28:37 by vbackyet          #+#    #+#             */
/*   Updated: 2021/12/10 17:32:14 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_export(t_env *export, t_env *temp)
{
	if (ft_strcmp(temp->key, export->key) == 0)
	{
		if (!export->content)
		{
			free (export->key);
			free (export->content);
			free (export);
			return (1);
		}
		temp->content = export->content;
		return (1);
	}
	return (0);
}

void	paste_env(t_env *export, t_env **envr)
{
	t_env	*temp;
	int		i;

	temp = *envr;
	while (temp-> next != NULL)
	{
		if (free_export(export, temp))
			return ;
		temp = temp->next;
	}	
	if (free_export(export, temp))
		return ;
	temp->next = export;
}

int	sum_of_lett(char *my_word, int to, int flag)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while ((my_word[i] != '\0') && (i <= to))
	{
		sum += (int)my_word[i];
		i++;
	}
	if (flag == -1)
		return (0);
	return (sum);
}

void	clean_the_stuff(t_env *beg, int from, int i)
{
	while (beg != NULL)
	{
		if ((sum_of_lett(beg->key, i, beg->flag) > from) && \
		(sum_of_lett(beg->key, i, beg->flag) != 0))
		{
			if (beg->flag != 1)
				beg->flag = -1;
		}
		beg = beg-> next;
	}
}
