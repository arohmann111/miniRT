/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 12:27:12 by afrasch           #+#    #+#             */
/*   Updated: 2021/10/25 21:11:53 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Iterates the list ’lst’ and applies the function’f’ to the content of each
   element. Creates a new list resulting of the successive applications of the
   function ’f’. The ’del’ function is used to delete the content of an element
   if needed. */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*element;
	t_list	*new;

	if (!lst)
		return (0);
	new = 0;
	while (lst)
	{
		element = ft_lstnew((*f)(lst->content));
		if (!element)
		{
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&new, element);
		lst = lst->next;
	}
	return (new);
}
