/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 20:56:58 by afrasch           #+#    #+#             */
/*   Updated: 2021/11/04 19:06:39 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Counts the digits of a number in base 10. */
static int	ft_digit_count(int nbr)
{
	int	digits;

	digits = 0;
	if (nbr <= 0)
		digits++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		digits++;
	}
	return (digits);
}

/* Allocates and returns a string representing the integer received as an
   argument. Returns NULL if allocation fails. */
char	*ft_itoa(int nbr)
{
	char	*result;
	int		digits;

	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	digits = ft_digit_count(nbr);
	result = (char *)malloc(digits + 1);
	if (!result)
		return (0);
	result[digits] = '\0';
	if (nbr < 0)
		result[0] = '-';
	else if (nbr == 0)
		result[0] = '0';
	while (nbr != 0)
	{
		--digits;
		if (nbr < 0)
			nbr *= -1;
		result[digits] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (result);
}
