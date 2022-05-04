/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 13:27:38 by afrasch           #+#    #+#             */
/*   Updated: 2021/10/25 21:14:16 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Takes a number and its base. Counts digits and returns the result. */
int	ft_intlen(long long num, int base)
{
	int	i;

	i = 1;
	while (num >= base || num <= -base)
	{
		i++;
		num /= base;
	}
	return (i);
}
