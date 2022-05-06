/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:57:53 by arohmann          #+#    #+#             */
/*   Updated: 2022/05/06 11:31:20 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int ac, char **av)
{
	if (ac != 2)
		return (print_error("wrong number of arguments\nTry: ./miniRT <file.rt>\n"));
	if (read_file(av[1]) == ERROR)
		return (print_error("File cannot be read\n"));
	return (0);
}