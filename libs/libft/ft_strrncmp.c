/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:56:13 by afrasch           #+#    #+#             */
/*   Updated: 2022/05/30 17:01:25 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Compares at most the last n bytes of str1 and str2. Returns 0 if they are
   identical or the amount of different chars
   (>0 if str1 more, <0 if str2 is more). */
int	ft_strrncmp(char *str1, char *str2, size_t n)
{
	size_t	i;
	size_t	k;
	size_t	a;

	if (n == 0)
		return (0);
	a = 0;
	i = ft_strlen(str1) - 1;
	k = ft_strlen(str2) - 1;
	while (i && k && str1[i] == str2[k] && a < n - 1)
	{
		i--;
		k--;
		a++;
	}
	return (((unsigned char *)str2)[k] - ((unsigned char *)str1)[i]);
}
