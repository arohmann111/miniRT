/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:23:22 by afrasch           #+#    #+#             */
/*   Updated: 2022/05/09 16:57:34 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	print_error(char *err_msg, int line_cnt)
{
	ft_putstr_fd("File error in line ", STDERR_FILENO);
	ft_putnbr_fd(line_cnt, STDERR_FILENO);
	write(STDERR_FILENO, ": ", 2);
	ft_putendl_fd(err_msg, STDERR_FILENO);
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

int	get_colors(t_colors *c, char *split_str, int line_cnt)
{
	char	**colors;
	int		i;
	int		error;
	int		rgb[3];

	i = 0;
	error = 0;
	colors = ft_split(split_str, ',');
	if (!colors)
		return (print_error("Split failed", line_cnt));
	if (arrlen(colors) != 3)
		return (print_error("Wrong number of colors", line_cnt));
	while (i < 3)
	{
		printf("color |%s|\n", colors[i]);
		rgb[i] = ft_atoi(colors[i], &error);
		if (error == ERROR)
			return (print_error("Color can't be converted", line_cnt));
		if (check_range(0.0, 255.0, (double)rgb[i]) == false)
			return(print_error("Color is not in range [0-255]", line_cnt));
		i++;
	}
	c->r = rgb[0];
	c->g = rgb[1];
	c->b = rgb[2];
	return (0);
}

// t_vec3d	normalise(t_vec3d v)
// {
// 	double	len;

// 	len = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
// 	v.x = v.x / len;
// 	v.y = v.y / len;
// 	v.z = v.z / len;
// 	return (v);
// }

int	get_vector(t_vec3d *v, char *split_str, int type, int line_cnt)
{
	char	**vector;
	int		i;
	int		error;
	double	xyz[3];

	i = 0;
	error = 0;
	vector = ft_split(split_str, ',');
	if (!vector)
		return (print_error("Split failed", line_cnt));
	if (arrlen(vector) != 3)
		return (print_error("Wrong number of vector coordinates", line_cnt));
	while (i < 3)
	{
		printf("vector |%s|\n", vector[i]);

		xyz[i] = ft_atod(vector[i], &error);
		if (error == ERROR)
			return (print_error("Vector can't be converted", line_cnt));
		if (type == COORDINATES)
		{
			if (check_range(-500.0, 500.0, xyz[i]) == false)
				return(print_error("Coordinate vector is not in range [-500.0,500.0]", line_cnt));
		}
		else if (type == ORIENTATION)
		{
			if (check_range(-1000.0, 1000.0, xyz[i]) == false)
				return(print_error("Orientation vector is not in range [-1000.0,1000.0]", line_cnt));
		}
		i++;
	}
	v->x = xyz[0];
	v->y = xyz[1];
	v->z = xyz[2];
	// if (type == ORIENTATION)
	// 	normalise(*v);
	return (0);
}

int get_ambiente(t_scene *scene, char **split, int line_cnt)
{
	double	ratio;
	int		error;

	if (scene->ambiente.is_set == true)
		return (print_error("Ambient light already exists", line_cnt));
	if (arrlen(split) != 3)
		return (print_error("Wrong ambient light input", line_cnt));
	ratio = ft_atod(split[1], &error);
	if (error == ERROR)
		return (print_error("Ambient light ratio can't be converted", line_cnt));
	if (check_range(0.0, 1.0, ratio) == false)
		return (print_error("Ambient light ratio is not in range [0.0,1.0]", line_cnt));
	scene->ambiente.ratio = ratio;
	if (get_colors(&scene->ambiente.colors, split[2], line_cnt) == ERROR)
		return (ERROR);
	scene->ambiente.is_set = true;
	return (0);
}

int get_camera(t_scene *scene, char **split, int line_cnt)
{
	int	field_of_view;
	int	error;

	field_of_view = 0;
	error = 0;
	if (scene->camera.is_set == true)
		return (print_error("Camera already exists", line_cnt));
	if (arrlen(split) != 4)
		return (print_error("Wrong camera input", line_cnt));
	if (get_vector(&scene->camera.pos, split[1], COORDINATES, line_cnt) == ERROR)
		return (ERROR);
	if (get_vector(&scene->camera.orient, split[2], ORIENTATION, line_cnt) == ERROR)
		return (ERROR);
	field_of_view = ft_atoi(split[3], &error);
	if (error == ERROR)
		return (print_error("Field of view can't be converted", line_cnt));
	if (check_range(0.0, 180.0, (double)field_of_view) == false)
		return (print_error("Field of view is not in range [0-180]", line_cnt));
	scene->camera.fov = field_of_view;
	scene->camera.is_set = true;
	return (0);
}

int	get_light(t_scene *scene, char **split, int line_cnt)
{
	int	brightness_ratio;
	int	error;

	brightness_ratio = 0;
	error = 0;
	if (scene->light.is_set == true)
		return (print_error("Light already exists", line_cnt));
	if (arrlen(split) != 4)
		return (print_error("Wrong light input", line_cnt));
	if (get_vector(&scene->light.pos, split[1], COORDINATES, line_cnt) == ERROR)
		return (ERROR);
	brightness_ratio = ft_atod(split[2], &error);
	if (error == ERROR)
		return (print_error("Brightness ratio can't be converted", line_cnt));
	if (check_range(0.0, 1.0, (double)brightness_ratio) == false)
		return (print_error("Brightness ratio is not in range [0.0,1.0]", line_cnt));
	//range in print_error angeben
	scene->light.bright = brightness_ratio;
	if (get_colors(&scene->light.colors, split[3], line_cnt) == ERROR)
		return (ERROR);
	scene->light.is_set = true;
	return (0);
}

int	get_resolution(t_scene *scene, char **split, int line_cnt)
{
	int	w;
	int	h;
	int	error;

	error = 0;
	if (scene->res.is_set == true)
		return (print_error("Resolution already exists", line_cnt));
	if (arrlen(split) != 3)
		return (print_error("Wrong resolution input", line_cnt));
	w = ft_atoi(split[1], &error);
	if (error == ERROR)
		return (print_error("Width can't be converted", line_cnt));
	h = ft_atoi(split[2], &error);
	if (error == ERROR)
		return (print_error("Height can't be converted", line_cnt));
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

int get_plane(t_scene *scene, char **split, int line_cnt)
{
	t_list		*new_elem;

	if (arrlen(split) != 4)
		return (print_error("Wrong plane input", line_cnt));
	new_elem = get_new_obj(PLANE);
	if (!new_elem)
		return (print_error("Plane obj can't be allocated", line_cnt));
	ft_lstadd_back(&scene->list, new_elem);
	// printf("check in function %s\n", __func__);
	if (get_vector(&((t_object*)new_elem->content)->pos, split[1], COORDINATES, line_cnt) == ERROR)
		return (ERROR);
	if (get_vector(&((t_object*)new_elem->content)->pl.orient, split[2], ORIENTATION, line_cnt) == ERROR)
		return (ERROR);
	if (get_colors(&((t_object*)new_elem->content)->colors, split[3], line_cnt) == ERROR)
		return (ERROR);
	return (0);
}

int get_sphere(t_scene *scene, char **split, int line_cnt)
{
	t_list	*new;
	double	dia;
	int		error;

	error = 0;
	if (arrlen(split) != 4)
		return (print_error("Wrong sphere input", line_cnt));
	new = get_new_obj(SPHERE);
	if (!new)
		return (print_error("Sphere object can't be allocated", line_cnt));
	ft_lstadd_back(&scene->list, new);
	if (get_vector(&((t_object*)new->content)->pos, split[1], COORDINATES, line_cnt) == ERROR)
		return (ERROR);
	dia = ft_atod(split[2], &error);
	if (error == ERROR)
		return (print_error("Sphere diameter can't be converted", line_cnt));
	((t_object*)new->content)->sp.diameter = dia;
	if (get_colors(&((t_object*)new->content)->colors, split[3], line_cnt) == ERROR)
		return (ERROR);
	return (0);
}

int	get_cylinder(t_scene *scene, char **split, int line_cnt)
{
	t_list	*new;
	double	dia;
	double	height;
	int		error;

	error = 0;
	if (arrlen(split) != 6)
		return (print_error("Wrong cylinder input", line_cnt));
	new = get_new_obj(CYLINDER);
	if (!new)
		return (print_error("Cylinder object can't be allocated", line_cnt));
	ft_lstadd_back(&scene->list, new);
	if (get_vector(&((t_object*)new->content)->pos, split[1], COORDINATES, line_cnt) == ERROR)
		return (ERROR);
	if (get_vector(&((t_object*)new->content)->cy.orient, split[2], ORIENTATION, line_cnt) == ERROR)
		return (ERROR);
	dia = ft_atod(split[3], &error);
	if (error == ERROR)
		return (print_error("Cylinder diameter can't be converted", line_cnt));
	((t_object*)new->content)->cy.diameter = dia;
	height = ft_atod(split[4], &error);
	if (error == ERROR)
		return (print_error("Cylinder height can't be converted", line_cnt));
	((t_object*)new->content)->cy.height = dia;
	if (get_colors(&((t_object*)new->content)->colors, split[5], line_cnt) == ERROR)
		return (ERROR);
	return (0);
}

int	get_obj(t_scene *scene, char **split, int line_cnt)
{
	if (split[0][0] == 'p' && split[0][1] == 'l')
		return (get_plane(scene, split, line_cnt));
	if (split[0][0] == 's' && split[0][1] == 'p')
		return (get_sphere(scene, split, line_cnt));
	if (split[0][0] == 'c' && split[0][1] == 'y')
		return (get_cylinder(scene, split, line_cnt));
	else
		return (print_error("Object type doesn't exist", line_cnt));
}

int	parsing(t_scene *scene, char *line, int line_cnt)
{
	int i;
	char **split;

	i = 0;
	if (line[0] == '\n')
		return (0);
	split = ft_split(line, ' ');
	if (split == NULL)
		return (print_error("Split failed", line_cnt));
	else if (split[0][0] == 'A')
		return (get_ambiente(scene, split, line_cnt));
	else if (split[0][0] == 'C')
		return (get_camera(scene, split, line_cnt));
	else if (split[0][0] == 'L')
		return (get_light(scene, split, line_cnt));
	else if (split[0][0] == 'R')
		return (get_resolution(scene, split, line_cnt));
	else
		return (get_obj(scene, split, line_cnt));
	return(0);
}

int	read_file(t_scene *scene, char *file)
{
	char	*line;
	int		fd;
	int		line_cnt;
	
	line = NULL;
	line_cnt = 0;
	fd = open(file, O_RDONLY);
	if (fd == ERROR)
		return (ERROR);
	while (1)
	{
		line = get_next_line(fd);
		line_cnt++;
		printf("|%s|\n", line);
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (line[0] == '#' || line[0] == '\n' || line[0] == '\0')
			continue ;
		if (parsing(scene, line, line_cnt) != 0)
			return (ERROR);
	}
	return (0);
}
