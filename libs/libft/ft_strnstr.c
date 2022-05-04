/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:58:16 by afrasch           #+#    #+#             */
/*   Updated: 2021/10/25 21:53:06 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Locates the first occurrence of the null-terminated needle in haystack, where
   not more than len characters are searched. Returns NULL if needle isn't found
   or haystack if needle is empty, otherwise a pointer to needle. */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*needle || needle == 0)
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
