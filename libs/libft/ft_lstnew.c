/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:15:36 by afrasch           #+#    #+#             */
/*   Updated: 2021/10/25 21:11:40 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates and returns a new element. The variable ’content’ is initialized
   with the value of the parameter ’content’. The variable ’next’ is initialized
   to NULL.  */
t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == 0)
		return (0);
	new->content = content;
	new->next = 0;
	return (new);
}
