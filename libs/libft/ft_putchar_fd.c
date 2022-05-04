/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:55:35 by afrasch           #+#    #+#             */
/*   Updated: 2021/10/25 21:11:07 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the character ’c’ to the given filedescriptor. */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
