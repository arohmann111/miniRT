/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 17:26:41 by afrasch           #+#    #+#             */
/*   Updated: 2021/12/06 15:06:27 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Checks for empty string, right chars as input, prefix only at the beginning,
   if there is only one prefix, if sign exists. */
static void	ft_atoi_inputcheck(const char *str, int *error, int *sign)
{
	int	i;
	int	prefix;

	i = 0;
	prefix = 0;
	while (str && str[i])
	{
		if (ft_strchr("0123456789-+", str[i]) == 0)
			break ;
		if (str[i] == '-' || str[i] == '+')
		{
			prefix++;
			if (i > 0)
				*error = -1;
		}
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	if (prefix > 1 || str[i] != '\0' || !str)
		*error = -1;
}

/* Checks if atoi did the right job by converting its output back to a string
   and comparing the result with the original string */
static int	ft_is_int(const char *str, int input)
{
	char	*temp;

	temp = ft_itoa(input);
	if (str[0] == '+')
		str = str + 1;
	if (!ft_strcmp(temp, str))
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

/* Turns ascii into an integer. Skipps spaces, checks and puts sign,
   then transfers to int. Returns the int or 0 if it failed. */
int	ft_atoi(const char *str, int *error)
{
	int	result;
	int	i;
	int	sign;

	result = 0;
	i = 0;
	sign = 1;
	ft_atoi_inputcheck(str, error, &sign);
	if (*error == -1)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] > 47 && str[i] < 58)
		result = result * 10 + str[i++] - 48;
	if (ft_is_int(str, sign * result) == 1)
		return (sign * result);
	*error = -1;
	return (0);
}
