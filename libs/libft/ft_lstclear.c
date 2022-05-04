/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:14:18 by afrasch           #+#    #+#             */
/*   Updated: 2021/11/06 19:20:15 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Conductor goes through the whole list, deletes and frees the given element
   and every next element, using the function ’del’and free(3).
   The pointer to the list is set to NULL. */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*conductor;

	conductor = *lst;
	while (conductor != NULL)
	{
		*lst = conductor->next;
		del(conductor->content);
		free(conductor);
		conductor = *lst;
	}
}
