/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:11:32 by afrasch           #+#    #+#             */
/*   Updated: 2021/10/25 21:11:30 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Searches for the first occurrence of the character c in the first n bytes
   of the string pointed to by str. */
void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)str)[i] == (unsigned char)c)
			return ((unsigned char *)str + i);
		i++;
	}
	return (0);
}
