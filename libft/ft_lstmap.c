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
