/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 17:54:03 by afrasch           #+#    #+#             */
/*   Updated: 2021/10/25 21:11:15 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copies n characters from src to dest, but for overlapping memory blocks.
   Returns a pointer to the destination. */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (src < dest)
		while (n--)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	else if (dest < src)
		ft_memcpy(dest, src, n);
	return (dest);
}
