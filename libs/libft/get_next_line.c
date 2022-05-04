/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 19:44:23 by afrasch           #+#    #+#             */
/*   Updated: 2021/12/21 14:31:29 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*freeing(char *str1)
{
	free(str1);
	return (NULL);
}

static int	newline(char *find)
{
	int	i;

	i = 0;
	if (!find)
		return (-1);
	while (find[i])
	{
		if (find[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*get_line(char **memory)
{
	char	*temp;
	char	*line;
	int		length;

	temp = *memory;
	if (newline(*memory) > -1)
	{
		length = newline(*memory) + 1;
		line = ft_substr(*memory, 0, length);
		*memory = ft_substr(*memory, length, ft_strlen(*memory) - length);
	}
	else
	{
		line = ft_substr(*memory, 0, ft_strlen(*memory));
		*memory = NULL;
	}
	free(temp);
	return (line);
}

static char	*free_memory(char *temp, char *memory, char *buffer)
{
	temp = ft_strjoin(memory, buffer);
	free(memory);
	memory = temp;
	return (memory);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*memory;
	char		*temp;
	int			reading;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reading = 1;
	temp = NULL;
	while (reading > 0)
	{
		if (ft_strchr(memory, '\n'))
			break ;
		reading = read(fd, buffer, BUFFER_SIZE);
		if (reading == -1 || (reading == 0 && memory == NULL))
			return (freeing(memory));
		buffer[reading] = '\0';
		if (memory == 0)
			memory = ft_strdup(buffer);
		else
			memory = free_memory(temp, memory, buffer);
	}
	if (memory == NULL || memory[0] == '\0')
		return (freeing(memory));
	return (get_line(&memory));
}
