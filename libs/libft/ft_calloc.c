/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:14:50 by afrasch           #+#    #+#             */
/*   Updated: 2022/04/14 16:31:58 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates and returns a string for count elements and fills it up with 0s.
   Size is the sizeof one element (e.g. int). */
void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	if (size && SIZE_MAX / size > count)
		return (NULL);
	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}
