/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:22:18 by afrasch           #+#    #+#             */
/*   Updated: 2022/06/30 14:22:47 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	print_error(char *err_msg, int line_cnt, char **arr)
{
	ft_putstr_fd("Error in line ", STDERR_FILENO);
	ft_putnbr_fd(line_cnt, STDERR_FILENO);
	write(STDERR_FILENO, ":\n", 2);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	return (error_free(ERROR, arr));
}

int	error_free(int error, char **arr)
{
	if (arr != NULL)
	{
		ft_free_array(arr);
		arr = NULL;
	}
	return (error);
}

int	print_input_instructions(void)
{
	ft_putendl_fd("Error\nWrong number of arguments", STDERR_FILENO);
	ft_putendl_fd("Try: ./miniRT <file.rt>", STDERR_FILENO);
	return (ERROR);
}
