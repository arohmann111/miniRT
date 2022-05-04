/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 17:49:22 by afrasch           #+#    #+#             */
/*   Updated: 2021/10/25 21:11:11 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copies c (as an unsigned char) to the first n characters of the string
   pointed to by str. Returns a pointer to the memory area str. */
void	*ft_memset(void *str, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)str)[i] = (unsigned char)c;
		i++;
	}
	return (str);
}
