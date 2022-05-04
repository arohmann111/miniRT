/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:40:03 by afrasch           #+#    #+#             */
/*   Updated: 2021/11/04 15:47:14 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Compares str1 and str2. Returns 0 if they are identical or the amount of
   different chars (>0 if str1 more, <0 if str2 is more). */
int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != 0 && str1[i] == str2[i])
		i++;
	return (((unsigned char *)str1)[i] - ((unsigned char *)str2)[i]);
}
