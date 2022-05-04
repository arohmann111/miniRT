/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:19:09 by arohmann          #+#    #+#             */
/*   Updated: 2022/05/03 20:00:01 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	save_parameters_in_struct(char *line);

int	input_check(char *line)
{
	check_name();
	check_range();
}

int	read_file(char *file)
{
	char	*line;
	int		size;
	int		fd;
	
	line = NULL;
	size = 0;
	fd = open(file, O_RDONLY);
	if (fd == ERROR)
		return (ERROR);
	while (1)
	{
		if (line == NULL)
			break ;
		line = get_next_line(fd);
		printf("%s\n", line);
		input_check(line);
		save_parameters_in_struct(line);
	}
	return (0);
}
