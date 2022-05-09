/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:23:22 by afrasch           #+#    #+#             */
/*   Updated: 2022/05/09 14:47:11 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	print_error(char *err_msg)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	return (ERROR);
}

bool	check_range(double range_start, double range_end, double val)
{
	if (!(val >= range_start && val <= range_end))
		return (false);
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

int	get_colors(t_colors *c, char *split_str)
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
		printf("color |%s|\n", colors[i]);
		rgb[i] = ft_atoi(colors[i], &error);
		if (error == ERROR)
			return (print_error("Color can't be converted\n"));
		if (check_range(0.0, 255.0, (double)rgb[i]) == false)
			return(print_error("Color is not in range [0-255]\n"));
		i++;
	}
	c->r = rgb[0];
	c->g = rgb[1];
	c->b = rgb[2];
	return (0);
}

int	get_vector(t_vec3d *v, char *split_str, int type)
{
	char	**vector;
	int		i;
	int		error;
	double	xyz[3];

	i = 0;
	error = 0;
	vector = ft_split(split_str, ',');
	if (!vector)
		return (print_error("Split\n"));
	if (arrlen(vector) != 3)
		return (print_error("Wrong number of vector coordinates\n"));
	while (i < 3)
	{
		printf("vector |%s|\n", vector[i]);

		xyz[i] = ft_atod(vector[i], &error);
		if (error == ERROR)
			return (print_error("Vector can't be converted\n"));
		if (type == COORDINATES)
		{
			if (check_range(-500.0, 500.0, xyz[i]) == false)
				return(print_error("Coordinate vector is not in range [-500.0,500.0]\n"));
		}
		else if (type == ORIENTATION)
		{
			if (check_range(-1.0, 1.0, xyz[i]) == false)
				return(print_error("Orientation vector is not in range [-1.0,1.0]\n"));
		}
		i++;
	}
	// normalise();
	v->x = xyz[0];
	v->y = xyz[1];
	v->z = xyz[2];
	return (0);
}

int get_ambiente(t_scene *scene, char **split)
{
	double	ratio;
	int		error;

	if (scene->ambiente.is_set == true)
		return (print_error("Ambient light already exists\n"));
	if (arrlen(split) != 3)
		return (print_error("Wrong ambient light input\n"));
	ratio = ft_atod(split[1], &error);
	if (error == ERROR)
		return (print_error("Ambient light ratio can't be converted\n"));
	if (check_range(0.0, 1.0, ratio) == false)
		return (print_error("Ambient light ratio is not in range [0.0,1.0]\n"));
	scene->ambiente.ratio = ratio;
	if (get_colors(&scene->ambiente.colors, split[2]) == ERROR)
		return (ERROR);
	scene->ambiente.is_set = true;
	return (0);
}

int get_camera(t_scene *scene, char **split)
{
	int	field_of_view;
	int	error;

	field_of_view = 0;
	error = 0;
	if (scene->camera.is_set == true)
		return (print_error("Camera already exists\n"));
	if (arrlen(split) != 4)
		return (print_error("Wrong camera input\n"));
	if (get_vector(&scene->camera.pos, split[1], COORDINATES) == ERROR)
		return (ERROR);
	if (get_vector(&scene->camera.orient, split[2], ORIENTATION) == ERROR)
		return (ERROR);
	field_of_view = ft_atoi(split[3], &error);
	if (error == ERROR)
		return (print_error("Field of view can't be converted\n"));
	if (check_range(0.0, 180.0, (double)field_of_view) == false)
		return (print_error("Field of view is not in range [0-180]\n"));
	scene->camera.fov = field_of_view;
	scene->camera.is_set = true;
	return (0);
}

int	get_light(t_scene *scene, char **split)
{
	int	brightness_ratio;
	int	error;

	brightness_ratio = 0;
	error = 0;
	if (scene->light.is_set == true)
		return (print_error("Light already exists\n"));
	if (arrlen(split) != 4)
		return (print_error("Wrong light input\n"));
	if (get_vector(&scene->light.pos, split[1], COORDINATES) == ERROR)
		return (ERROR);
	brightness_ratio = ft_atod(split[2], &error);
	if (error == ERROR)
		return (print_error("Brightness ratio can't be converted\n"));
	if (check_range(0.0, 1.0, (double)brightness_ratio) == false)
		return (print_error("Brightness ratio is not in range [0.0,1.0]\n"));
	//range in print_error angeben
	scene->light.bright = brightness_ratio;
	if (get_colors(&scene->light.colors, split[3]) == ERROR)
		return (ERROR);
	scene->light.is_set = true;
	return (0);
}

int	get_resolution(t_scene *scene, char **split)
{
	int	w;
	int	h;
	int	error;

	error = 0;
	if (scene->res.is_set == true)
		return (print_error("Resolution already exists\n"));
	if (arrlen(split) != 3)
		return (print_error("Wrong resolution input\n"));
	w = ft_atoi(split[1], &error);
	if (error == ERROR)
		return (print_error("Width can't be converted\n"));
	h = ft_atoi(split[2], &error);
	if (error == ERROR)
		return (print_error("Height can't be converted\n"));
	printf("res w |%d| h |%d|\n", w, h);
	scene->res.width = w;
	scene->res.height = h;
	scene->res.is_set = true;
	return (0);
}

t_list	*get_new_obj(int type)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object) * 1);
	if (!obj)
		return (NULL);
	obj->type = type;
	return (ft_lstnew(obj));
}

int get_plane(t_scene *scene, char **split)
{
	t_list		*new_elem;

	if (arrlen(split) != 4)
		return (print_error("Wrong plane input\n"));
	new_elem = get_new_obj(PLANE);
	if (!new_elem)
		return (print_error("Plane obj can't be allocated\n"));
	ft_lstadd_back(&scene->list, new_elem);
	// printf("check in function %s\n", __func__);
	if (get_vector(&((t_object*)new_elem->content)->pos, split[1], COORDINATES) == ERROR)
		return (ERROR);
	if (get_vector(&((t_object*)new_elem->content)->pl.orient, split[2], ORIENTATION) == ERROR)
		return (ERROR);
	if (get_colors(&((t_object*)new_elem->content)->colors, split[3]) == ERROR)
		return (ERROR);
	return (0);
}

int get_sphere(t_scene *scene, char **split)
{
	t_list	*new;
	double	dia;
	int		error;

	error = 0;
	if (arrlen(split) != 4)
		return (print_error("Wrong sphere input\n"));
	new = get_new_obj(SPHERE);
	if (!new)
		return (print_error("Sphere object can't be allocated\n"));
	ft_lstadd_back(&scene->list, new);
	if (get_vector(&((t_object*)new->content)->pos, split[1], COORDINATES) == ERROR)
		return (ERROR);
	dia = ft_atod(split[2], &error);
	if (error == ERROR)
		return (print_error("Sphere diameter can't be converted\n"));
	((t_object*)new->content)->sp.diameter = dia;
	if (get_colors(&((t_object*)new->content)->colors, split[3]) == ERROR)
		return (ERROR);
	return (0);
}

int	get_cylinder(t_scene *scene, char **split)
{
	t_list	*new;
	double	dia;
	double	height;
	int		error;

	error = 0;
	if (arrlen(split) != 6)
		return (print_error("Wrong cylinder input\n"));
	new = get_new_obj(CYLINDER);
	if (!new)
		return (print_error("Cylinder object can't be allocated\n"));
	ft_lstadd_back(&scene->list, new);
	if (get_vector(&((t_object*)new->content)->pos, split[1], COORDINATES) == ERROR)
		return (ERROR);
	if (get_vector(&((t_object*)new->content)->cy.orient, split[2], ORIENTATION) == ERROR)
		return (ERROR);
	dia = ft_atod(split[3], &error);
	if (error == ERROR)
		return (print_error("Cylinder diameter can't be converted\n"));
	((t_object*)new->content)->cy.diameter = dia;
	height = ft_atod(split[4], &error);
	if (error == ERROR)
		return (print_error("Cylinder height can't be converted\n"));
	((t_object*)new->content)->cy.height = dia;
	if (get_colors(&((t_object*)new->content)->colors, split[5]) == ERROR)
		return (ERROR);
	return (0);
}

int	get_obj(t_scene *scene, char **split)
{
	if (split[0][0] == 'p' && split[0][1] == 'l')
		return (get_plane(scene, split));
	if (split[0][0] == 's' && split[0][1] == 'p')
		return (get_sphere(scene, split));
	if (split[0][0] == 'c' && split[0][1] == 'y')
		return (get_cylinder(scene, split));
	else
		return (ERROR);//wrong letter
}

int	parsing(t_scene *scene, char *line)
{
	int i;
	char **split;

	i = 0;
	if (line[0] == '\n')
		return (0);
	split = ft_split(line, ' ');
	if (split == NULL)
		return (print_error("Split\n"));
	else if (split[0][0] == 'A')
		return (get_ambiente(scene, split));
	else if (split[0][0] == 'C')
		return (get_camera(scene, split));
	else if (split[0][0] == 'L')
		return (get_light(scene, split));
	else if (split[0][0] == 'R')
		return (get_resolution(scene, split));
	else
		return (get_obj(scene, split));
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
		//line counter for print_error
		line = get_next_line(fd);
		printf("|%s|\n", line);
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (line[0] == '#' || line[0] == '\n' || line[0] == '\0')
			continue ;
		if (parsing(scene, line) != 0)
			return (ERROR);
	}
	return (0);
}
