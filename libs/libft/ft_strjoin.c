/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:30:41 by afrasch           #+#    #+#             */
/*   Updated: 2021/10/25 21:09:16 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates and returns a new string, which is the result of joining
   ’s1’ and ’s2’. */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	int		total_length;
	char	*str;

	if (!s1 || !s2)
		return (0);
	total_length = (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	str = (char *) malloc(sizeof(char) * total_length);
	if (str == 0)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
