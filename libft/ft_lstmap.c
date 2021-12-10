/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:33:53 by vbackyet          #+#    #+#             */
/*   Updated: 2021/12/10 17:33:54 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*temp;

	if (!lst || !f)
		return (NULL);
	newlst = ft_lstnew(f(lst->content));
	temp = newlst;
	lst = lst->next;
	while (lst)
	{	
		temp->next = ft_lstnew(f(lst->content));
		if (temp->next == NULL)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		temp = temp->next;
		lst = lst->next;
	}
	return (newlst);
}
