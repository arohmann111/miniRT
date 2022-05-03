/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:19:09 by arohmann          #+#    #+#             */
/*   Updated: 2022/05/03 15:34:46 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	read_file(char *file)
{
	FILE	*file;
	char	*line;
	int		size;
	
	line = NULL;
	size = 0;
	file = fopen(file, O_RDONLY);
	if (file == NULL)
		return (ERROR);
	while (getline(&line, &size, file) != EOF)
	{
		
	}
	
}