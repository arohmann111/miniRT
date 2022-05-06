/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:19:09 by arohmann          #+#    #+#             */
/*   Updated: 2022/05/06 11:14:40 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// int	save_parameters_in_struct(char *line);

bool	check_range(double range_start, double range_end, double val);

int	print_error(char *err_msg)
{
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	return (ERROR);
}

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

bool	is_comma(char c)
{
	if (c != ',')
	{
		print_error("parameters badly formatted\n");
		return (true);
	}
	return (false);
}

// int	next(char *str, int *i, int ident)
// {
// 	if (ident == NEXT_NUM)
// 	{
// 		while (str[*i] != '\0' && str[*i] != '\n' && is_whitespace(str[*i] == true))
// 			(*i)++;
// 	}
// 	else if (ident == NEXT_SPACE)
// 	{
// 		while (str[*i] != '\0' && str[*i] != '\n' && is_whitespace(str[*i]) == false )
// 			(*i)++;
// 	}
// 	return (*i);
// }

int	next(char *str, int *i, int ident)
{
	if (ident == NEXT_NUM)
	{
		while (is_whitespace(str[*i]) == true && str[*i] != '\0' && str[*i] != '\n')
			(*i)++;
	}
	else if (ident == NEXT_SPACE)
	{
		while (is_whitespace(str[*i]) == false && str[*i] != '\0' && str[*i] != '\n')
			(*i)++;
	}
	return (*i);
}

int	check_colors(char *colors)
{
	int	i;
	int	rgb;
	int num;
	int start;
	int err;
	char *tmp;

	i = 0;
	err = 0;
	rgb = 0;
	while (rgb < 3)
	{
		num = 0;
		start = i;
		while(colors[i] != '\0' && colors[i] != ',' && is_whitespace(colors[i]) == false)
			i++;
		if (colors[i] == '\0')
			i--;
		tmp = ft_substr(colors, start, i - start);
		if (colors[i] == ',')
			i++;
		num = ft_atoi(tmp, &err);
		if (err == ERROR)
		{
			free(tmp);
		}
		if (check_range(0.0, 255.0, (double)num) == false)
		{
			free(tmp);
			return (print_error("not in range\n"));
		}
		free(tmp);
		tmp = NULL;
		rgb++;
	}
	return (0);
}

int	check_3doubles(char *colors, double range_start, double range_end)
{
	int	i;
	int	xyz;
	int num;
	int start;
	int err;
	char *tmp;

	i = 0;
	err = 0;
	xyz = 0;
	while (xyz < 3)
	{
		num = 0;
		start = i;
		while(colors[i] != '\0' && colors[i] != ',' && is_whitespace(colors[i]) == false)
			i++;
		if (colors[i] == '\0')
			i--;
		tmp = ft_substr(colors, start, i - start);
		if (colors[i] == ',')
			i++;
		num = ft_atod(tmp, &err);
		if (err == ERROR)
		{
			free(tmp);
			return (print_error("not a valid int\n"));
		}
		if (check_range(range_start, range_end, (double)num) == false)
		{
			free(tmp);
			return (print_error("not in range\n"));
		}
		free(tmp);
		tmp = NULL;
		xyz++;
	}
	return (0);
}

int	check_a_light(char *line)
{
	int		i;
	int		start;
	int		a_light_cnt;
	int		err;
	char	*tmp;
	double	ratio;

	i = 1;
	err = 0;
	a_light_cnt = 0;
	if (a_light_cnt == 1)
		return (print_error("ambient lighting can only be set once\n"));
	else
		a_light_cnt = 1;
	next(line, &i, NEXT_NUM);
	start =  i;
	next(line, &i, NEXT_SPACE);
	tmp = ft_substr(line, start, i - start);
	ratio = ft_atod(tmp, &err);
	if (err == ERROR)
	{
		free(tmp);
		return (print_error("not a valid double\n"));
	}
	if (check_range(0.0, 1.0, ratio) == false)
	{
		free(tmp);
		return (print_error("not in range\n"));
	}
	free(tmp);
	next(line, &i, NEXT_NUM);
	start =  i;
	next(line, &i, NEXT_SPACE);
	tmp = ft_substr(line, start, i - start);
	if (check_colors(tmp) == ERROR)
		return (print_error("not a valid color\n"));
	return (0);
}

int	check_camera(char *line)
{
	char	*tmp;
	int	i;
	int	start;
	int	num;
	int	err;
	
	err = 0;
	i = 1;
	next(line, &i, NEXT_NUM);
	start =  i;
	next(line, &i, NEXT_SPACE);
	tmp = ft_substr(line, start, i - start);
	if (check_3doubles(tmp, -9999.0, 9999.0) == ERROR)
		return (ERROR);
	free(tmp);
	next(line, &i, NEXT_NUM);
	start =  i;
	next(line, &i, NEXT_SPACE);
	tmp = ft_substr(line, start, i - start);
	if (check_3doubles(tmp, -1.0, 1.0) == ERROR)
		return (ERROR);
	free(tmp);
	next(line, &i, NEXT_NUM);
	start =  i;
	next(line, &i, NEXT_SPACE);
	tmp = ft_substr(line, start, i - start);
	num = ft_atoi(tmp, &err);
	if (err == ERROR)
	{
		free(tmp);
		return (print_error("not a valid int\n"));
	}
	if (check_range(0.0, 180.0, (double)num) == false)
	{
		free(tmp);
		return (ERROR);
	}
	free(tmp);
	return (0);
}

int	check_scene_item(char *type, char *line)
{
	if (type[0] == 'A')
		return (check_a_light(line));
	else if (type[0] == 'C')
		return(check_camera(line));
	// else if (type[0] == 'L')
	// 	return(check_light());
	// else if (ft_strcmp("sp", type) == 0)
	// 	return(check_sphere());
	// else if (ft_strcmp("pl", type) == 0)
	// 	return(check_plane());
	// else if (ft_strcmp("cy", type) == 0)
	// 	return(check_cylinder());
	return (ERROR);
}

bool	check_range(double range_start, double range_end, double val)
{
	if (!(val >= range_start && val <= range_end))
	{
		print_error("value not in range\n");
		return (false);
	}
	return (true);
}


int	input_check(char *line)
{
	int i;
	int a;
	char *type;

	i = 0;
	if (line[0] == '\n')
		return (0);
	next(line, &i, NEXT_SPACE);
	type = ft_substr(line, 0, i);
	if ((a = check_scene_item(type, line)) == ERROR)
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
		line = get_next_line(fd);
		printf("|%s|\n", line);
		if (line == NULL)
			break ;
		if (line[0] == '#')
			continue ;
		if (input_check(line) != 0)0
			return (ERROR);
		// save_parameters_in_struct(line);
	}
	return (0);
}
