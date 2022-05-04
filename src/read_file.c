/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:19:09 by arohmann          #+#    #+#             */
/*   Updated: 2022/05/04 19:22:16 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	save_parameters_in_struct(char *line);

void	print_error(char *err_msg)
{
	write(STDERR_FILENO, str, ft_strlen(str));
}

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

/* int	check_three_doubles(char *line)
{

}

int	check_doule()
{
	
}

int	check_a_light(char *line)
{
	int	i;
	int	len;
	int	count;
	char *s_double;

	i = 1;
	count = 0;
	while (count < 3 && line[i] != NULL)
	{
		while (is_whitespace(str[i] == true && line[i] != NULL)
			i++;
		len = 0;
		while (line[i] != ',' && line[i] != NULL)
			len+++;
		if (str[i] == NULL)
			return (ERROR);
		if (str[i] == ',')
			count++;
		s_double =  ft_substr(line, i, len);
		if (check_double(s_double) == ERROR)
			return (ERROR);
		i++;
	}
} */

int	check_scene_item(char *type, char *line)
{
	if (type[0] == 'A')
		return (check_a_light(line));
	else if (type[0] == 'C')
		return(check_camera());
	else if (type[0] == 'L')
		return(check_light());
	else if (ft_strcmp("sp", type) == 0)
		return(check_sphere());
	else if (ft_strcmp("pl", type) == 0)
		return(check_plane());
	else if (ft_strcmp("cy", type) == 0)
		return(check_cylinder());
	return (0);
}

bool	check_range(int range_start, int range_end, int val)
{
	if (val => range_start && val <= range_end)
		return (true);
	return (false);
}


int	input_check(char *line)
{
	int i;
	char *type;

	i = 0;
	while (is_whitespace(line[i]))
		i++;
	type = ft_substr(line, 0, i);
	if (check_name(type, line) == ERROR)
	{
		free(type);
		return (ERROR);
	}
	free(type);
	return(0);
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
		if (line[i] == '#')
			continue ;
		if (input_check(line) != 0)
			return (ERROR);
		save_parameters_in_struct(line);
	}
	return (0);
}
