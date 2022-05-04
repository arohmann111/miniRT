/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 15:30:54 by afrasch           #+#    #+#             */
/*   Updated: 2021/10/25 21:28:40 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copies up to size - 1 characters from the NUL-terminated string src to dst,
   NUL-terminating the result. Returns the length of src. */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	while ((i + 1) < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (size)
		dst[i] = '\0';
	return (ft_strlen((char *)src));
}
