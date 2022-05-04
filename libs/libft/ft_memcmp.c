/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:45:54 by afrasch           #+#    #+#             */
/*   Updated: 2021/10/25 21:11:26 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* compares the first n bytes of memory area str1 and memory area str2.
   if Return value < 0 then it indicates str1 is less than str2.
   if Return value > 0 then it indicates str2 is less than str1.
   if Return value = 0 then it indicates str1 is equal to str2. */
int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t	i;

	if (!str1 && !str2)
		return (0);
	i = 0;
	while (i < n)
	{
		if (((unsigned char *)str1)[i] != ((unsigned char *)str2)[i])
			return (((unsigned char *)str1)[i] - ((unsigned char *)str2)[i]);
		i++;
	}
	return (0);
}
