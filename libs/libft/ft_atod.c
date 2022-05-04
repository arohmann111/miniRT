/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:02:37 by afrasch           #+#    #+#             */
/*   Updated: 2021/10/25 21:23:43 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Checks for empty string, right chars as input, prefix only at the beginning,
   if prefix & comma exist only once, if sign exists, and double size (16) */
static void	ft_atod_inputcheck(const char *str, int *error, int *sign)
{
	int	i;
	int	prefix;
	int	point;

	i = 0;
	prefix = 0;
	point = 0;
	while (str && str[i])
	{
		if (ft_strchr("0123456789-+.,", str[i]) == 0)
			break ;
		if (str[i] == '-' || str[i] == '+')
		{
			prefix++;
			if (i > 0)
				*error = -1;
		}
		if (str[i] == '.' || str[i] == ',')
			point++;
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	if (i > 16 || prefix > 1 || point > 1 || str[i] != '\0' || !str)
		*error = -1;
}

/* Converts a string to a double. In case of a failure, *error is set to -1,
   which must be checked every time after ft_atod is called.*/
double	ft_atod(const char *str, int *error)
{
	double	result;
	double	divisor;
	int		sign;
	int		i;

	result = 0;
	divisor = 1;
	sign = 1;
	i = 0;
	ft_atod_inputcheck(str, error, &sign);
	if (*error == -1)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '.' && str[i] != ',' && str[i])
		result = result * 10 + str[i++] - '0';
	if (str[i] == '.' || str[i] == ',')
		i++;
	while (str[i])
	{
		result = (result * 10 + str[i++] - '0');
		divisor /= 10;
	}
	return (result * sign * divisor);
}
