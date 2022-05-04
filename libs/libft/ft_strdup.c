/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:34:44 by afrasch           #+#    #+#             */
/*   Updated: 2021/10/25 21:09:37 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates and duplicates str. Returns a pointer to the new string */
char	*ft_strdup(const char *str)
{
	int		i;
	char	*dest;

	i = ft_strlen((char *)str);
	dest = (char *)malloc(i + 1);
	if (dest == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
