/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:23:22 by afrasch           #+#    #+#             */
/*   Updated: 2022/05/06 13:44:21 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	print_error(char *err_msg)
{
	write(STDERR_FILENO, "Error:", 6);
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
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

int	arrlen(char **arr)
{
	int	i;

	i = 1;
	if (!arr)
		return (-1);
	while (arr[i])
		i++;
	return (i);
}

int	get_colors(t_object *object, char *split_str)
{
	char	**colors;
	int		i;
	int		error;
	int		rgb[3];

	i = 0;
	error = 0;
	colors = ft_split(split_str, ',');
	if (!colors)
		return (print_error("Split\n"));
	if (arrlen(colors) != 3)
		return (print_error("Wrong number of colors\n"));
	while (i < 3)
	{
		rgb[i] = ft_atoi(colors[i], &error);
		if (error == ERROR)
			return (print_error("Color can't be converted\n"));
		if (check_range(0.0, 255.0, (double)rgb[i]) == false)
			return(print_error("Color is not in range\n"));
		i++;
	}
	(void)object;
	return (0);
}

int	get_vector(t_object *object, char *split_str, int type)
{
	char	**vector;
	int		i;
	int		error;
	int		xyz[3];

	i = 0;
	error = 0;
	vector = ft_split(split_str, ',');
	if (!vector)
		return (print_error("Split\n"));
	if (arrlen(vector) != 3)
		return (print_error("Wrong number of vector coordinates\n"));
	while (i < 3)
	{
		xyz[i] = ft_atod(vector[i], &error);
		if (error == ERROR)
			return (print_error("Vector can't be converted\n"));
		if (type == COORDINATES)
		{
			if (check_range(-500.0, 500.0, xyz[i]) == false)
				return(print_error("Coordinate vector is not in range\n"));
		}
		else if (type == ORIENTATION)
		{
			if (check_range(-1.0, 1.0, xyz[i]) == false)
				return(print_error("Orientation vector is not in range\n"));
		}
		i++;
	}
	// normalise();
	(void)object;
	return (0);
}

int get_a_light(t_scene *scene, char **split)
{
	double	ratio;
	int		error;

	if (arrlen(split) != 3)
		return (print_error("Wrong ambient light input\n"));
	ratio = ft_atod(split[1], &error);
	if (error == ERROR)
		return (print_error("Ambient light ratio can't be converted\n"));
	if (check_range(0.0, 1.0, ratio) == false)
		return (print_error("Ambient light ratio is not in range\n"));
	if (get_colors(scene->object->(a_light)data, split[2]) == ERROR)
		return (ERROR);
	return (0);
}

int get_camera(t_scene *scene, char **split)
{
	int	field_of_view;
	int	error;

	field_of_view = 0;
	error = 0;
	if (arrlen(split) != 4)
		return (print_error("Wrong camera input\n"));
	if (get_vector(scene->object, split[1], COORDINATES) == ERROR)
		return (ERROR);
	if (get_vector(scene->object, split[2], ORIENTATION) == ERROR)
		return (ERROR);
	field_of_view = ft_atoi(split[3], &error);
	if (error == ERROR)
		return (print_error("Field of view can't be converted\n"));
	if (check_range(0.0, 180.0, (double)field_of_view) == false)
		return (print_error("Field of view is not in range\n"));
	//fov in struct speichern
	return (0);
}

int	get_light(t_scene *scene, char **split)
{
	int	brightness_ratio;
	int	error;

	brightness_ratio = 0;
	error = 0;
	if (arrlen(split) != 4)
		return (print_error("Wrong light input\n"));
	get_vector(scene->object, split[1], COORDINATES) == ERROR)
		return (ERROR);
	brightness_ratio = ft_atoi(split[2], &error);
	if (error == ERROR)
		return (print_error("Brightness ratio can't be converted\n"));
	if (check_range(0.0, 1.0, (double)brightness_ratio) == false)
		return (print_error("Brightness ratio is not in range\n"));
	//br in struct abspeichern
	if (get_colors(scene->object->(light)data, split[3]) == ERROR)
		return (ERROR);
	return (0);
}

int	parsing(t_scene *scene, char *line)
{
	int i;
	int a;
	char **split;

	i = 0;
	if (line[0] == '\n')
		return (0);
	split = ft_split(line, ' ');
	if (split == NULL)
		return (print_error("Split\n"));
	if (split[0][0] == 'A')
		return (get_a_light(scene, split));
	if (split[0][0] == 'C')
		return (get_camera(scene, split));
	if (split[0][0] == 'L')
		return (get_light(scene, split));
	return(0);
}

int	read_file(t_scene *scene, char *file)
{
	char	*line;
	int		fd;
	
	line = NULL;
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
		if (parsing(scene, line) != 0)
			return (ERROR);
	}
	return (0);
}