/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 08:59:56 by afrasch           #+#    #+#             */
/*   Updated: 2021/11/04 16:54:51 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Compares at most the first n bytes of str1 and str2. Returns 0 if they are
   identical or the amount of different chars
   (>0 if str1 more, <0 if str2 is more). */
int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] && str1[i] == str2[i] && i < n - 1)
		i++;
	return (((unsigned char *)str1)[i] - ((unsigned char *)str2)[i]);
}
