/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:41:29 by afrasch           #+#    #+#             */
/*   Updated: 2021/12/16 10:38:37 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Searches for the first occurrence of (typecasted char) c in str.
   Returns a pointer to it. */
char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	size_t	l;

	if (!str)
		return (NULL);
	i = 0;
	l = ft_strlen((char *)str);
	while (i <= l)
	{
		if (str[i] == (unsigned char)c)
			return ((char *)str + i);
		else
			i++;
	}
	return (NULL);
}
