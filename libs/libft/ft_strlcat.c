/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 15:30:49 by afrasch           #+#    #+#             */
/*   Updated: 2021/10/25 21:33:04 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Appends the NUL-terminated string src to the end of dest. It will append at
   most size - strlen(dest) - 1 bytes, NUL-terminating the result.
   Returns the total length of the created string tried to create, which means
   the initial length of dest plus the length of src. */
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	result;

	i = ft_strlen(dest);
	result = ft_strlen((char *)src);
	if (size <= i)
		result += size;
	else
		result += i;
	j = 0;
	while (src[j] && (i + 1) < size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (size > 0 && i <= size)
		dest[i] = '\0';
	return (result);
}
