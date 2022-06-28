/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:45:15 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/28 20:03:32 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
		return (print_error("Split failed", line_cnt, colors));
	if (arrlen(colors) != 3)
		return (print_error("Wrong number of colors", line_cnt, colors));
	while (i < 3)
	{
		rgb[i] = ft_atoi(colors[i], &error);
		if (error == ERROR)
			return (print_error("Color can't be converted", line_cnt, colors));
		if (check_range(0.0, 255.0, (double)rgb[i]) == false)
			return (print_error("Color is not in range [0-255]", line_cnt, colors));
		i++;
	}
	c->r = rgb[0];
	c->g = rgb[1];
	c->b = rgb[2];
	ft_free_array(colors);
	return (0);
}

int	get_material(t_object *obj, char *split_str, int line_cnt)
{
	char	**material;
	int		error;

	error = 0;
	material = ft_split(split_str, ',');
	if (!material)
		return (print_error("Split failed", line_cnt, NULL));
	if (arrlen(material) != 2)
		return (print_error("Wrong number of material factors", line_cnt, material));
	obj->matte = ft_atod(material[0], &error);
	if (error == ERROR)
		return (print_error("Matte material factor can't be converted", line_cnt, material));
	if (check_range(0.0, 1.0, obj->matte) == false)
		return(print_error("Material factor is not in range [0.0-1.0]", line_cnt, material));
	obj->spec = ft_atod(material[1], &error);
	if (error == ERROR)
		return (print_error("Specular material factor can't be converted", line_cnt, material));
	if (check_range(0.0, 1.0, obj->spec) == false)
		return(print_error("Material factor is not in range [0.0-1.0]", line_cnt, material));
	if (obj->matte + obj->spec != 1)
		return(print_error("Material factors must sum up to one", line_cnt, material));
	ft_free_array(material);
	return (0);
}

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
		return (print_error("Split failed", line_cnt, vector));
	if (arrlen(vector) != 3)
		return (print_error("Wrong number of vector coordinates", line_cnt, vector));
	while (i < 3)
	{
		xyz[i] = ft_atod(vector[i], &error);
		if (error == ERROR)
			return (print_error("Vector can't be converted", line_cnt, vector));
		if (type == COORDINATES)
		{
			if (check_range(-500.0, 500.0, xyz[i]) == false)
				return(print_error("Coordinate vector is not in range [-500.0,500.0]", line_cnt, vector));
		}
		else if (type == ORIENTATION)
		{
			if (check_range(-1000.0, 1000.0, xyz[i]) == false)//not important, but should be in resolution range
				return(print_error("Orientation vector is not in range [-1000.0,1000.0]", line_cnt, vector));
		}
		i++;
	}
	v->x = xyz[0];
	v->y = xyz[1];
	v->z = xyz[2];
	if (type == ORIENTATION)
		*v = norm_vec3d(*v);
	ft_free_array(vector);
	return (0);
}

int	get_ambiente(t_scene *scene, char **split, int line_cnt)
{
	double	ratio;
	int		error;

	if (scene->ambiente.is_set == true)
		return (print_error("Ambient light already exists", line_cnt, split));
	if (arrlen(split) != 3)
		return (print_error("Wrong ambient light input", line_cnt, split));
	ratio = ft_atod(split[1], &error);
	if (error == ERROR)
		return (print_error("Ambient light ratio can't be converted", line_cnt, split));
	if (check_range(0.0, 1.0, ratio) == false)
		return (print_error("Ambient light ratio is not in range [0.0,1.0]", line_cnt, split));
	scene->ambiente.ratio = ratio;
	if (get_colors(&scene->ambiente.colors, split[2], line_cnt) == ERROR)
		return (error_free(ERROR, split));
	scene->ambiente.colors.r = scene->ambiente.colors.r + 100;
	scene->ambiente.colors.g = scene->ambiente.colors.g + 100;
	scene->ambiente.colors.b = scene->ambiente.colors.b + 100;
	scale_color(scene->ambiente.colors);
	scene->ambiente.is_set = true;
	ft_free_array(split);
	return (0);
}

int get_camera(t_scene *scene, char **split, int line_cnt)
{
	int	field_of_view;
	int	error;

	field_of_view = 0;
	error = 0;
	if (scene->camera.is_set == true)
		return (print_error("Camera already exists", line_cnt, split));
	if (arrlen(split) != 4)
		return (print_error("Wrong camera input", line_cnt, split));
	if (get_vector(&scene->camera.pos, split[1], COORDINATES, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_vector(&scene->camera.orient, split[2], ORIENTATION, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	field_of_view = ft_atoi(split[3], &error);
	if (error == ERROR)
		return (print_error("Field of view can't be converted", line_cnt, split));
	if (field_of_view > 90)
		printf("\033[0;31mThat much field of view doesn't make sense, bro. Better stay under 60 degree.\033[m\n");
	if (check_range(1.0, 179.0, (double)field_of_view) == false)
		return (print_error("Field of view is not in range [1-179]", line_cnt, split));
	scene->camera.fov = field_of_view;
	scene->camera.is_set = true;
	ft_free_array(split);
	return (0);
}


int	get_resolution(t_scene *scene, char **split, int line_cnt)
{
	int	w;
	int	h;
	int	error;

	error = 0;
	if (scene->res.is_set == true)
		return (print_error("Resolution already exists", line_cnt, split));
	if (arrlen(split) != 3)
		return (print_error("Wrong resolution input", line_cnt, split));
	w = ft_atoi(split[1], &error);
	if (error == ERROR)
		return (print_error("Width can't be converted", line_cnt, split));
	h = ft_atoi(split[2], &error);
	if (error == ERROR)
		return (print_error("Height can't be converted", line_cnt, split));
	scene->res.width = w;
	scene->res.height = h;
	scene->res.is_set = true;
	ft_free_array(split);
	return (0);
}

int	get_background(t_scene *scene, char **split, int line_cnt)
{
	if (scene->bg.is_set == true)
		return (print_error("Background already exists", line_cnt, split));
	if (arrlen(split) != 2)
		return (print_error("Wrong background input", line_cnt, split));
	if (get_colors(&scene->bg.col, split[1], line_cnt) == ERROR)
		return (error_free(ERROR, split));
	scene->bg.is_set = true;
	ft_free_array(split);
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

t_list	*get_new_l(void)
{
	t_light	*l;

	l = (t_light *)malloc(sizeof(t_light) * 1);
	if (!l)
		return (NULL);
	return (ft_lstnew(l));
}


int	get_light(t_scene *scene, char **split, int line_cnt)
{
	t_list		*new_elem;
	double		brightness_ratio;
	int			error;

	brightness_ratio = 0.0;
	error = 0;
	if (arrlen(split) != 4)
		return (print_error("Wrong light input", line_cnt, split));
	new_elem = get_new_l();
	if (!new_elem)
		return (print_error("Light can't be allocated", line_cnt, split));
	ft_lstadd_back(&scene->lights, new_elem);
	if (get_vector(&((t_light *)new_elem->content)->pos, split[1], COORDINATES, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	brightness_ratio = ft_atod(split[2], &error);
	if (error == ERROR)
		return (print_error("Brightness ratio can't be converted", line_cnt, split));
	if (check_range(0.0, 1.0, brightness_ratio) == false)
		return (print_error("Brightness ratio is not in range [0.0,1.0]", line_cnt, split));
	((t_light *)new_elem->content)->bright = brightness_ratio;
	if (get_colors(&((t_light *)new_elem->content)->colors, split[3], line_cnt) == ERROR)
		return (error_free(ERROR, split));
	ft_free_array(split);
	return (0);
}

int	parsing(t_scene *scene, char *line, int line_cnt)
{
	//int i;
	char **split;

	//i = 0;
	if (line[0] == '\n')
		return (0);
	split = ft_split(line, ' ');
	if (split == NULL)
		return (print_error("Split failed", line_cnt, NULL));
	else if (split[0][0] == 'A')
		return (get_ambiente(scene, split, line_cnt));
	else if (split[0][0] == 'C')
		return (get_camera(scene, split, line_cnt));
	else if (split[0][0] == 'L')
		return (get_light(scene, split, line_cnt));
	else if (split[0][0] == 'R')
		return (get_resolution(scene, split, line_cnt));
	else if (split[0][0] == 'B')
		return (get_background(scene, split, line_cnt));
	else
		return (get_obj(scene, split, line_cnt));
	return(0);
}

int check_must_haves(t_scene *scene)
{
	if (scene->ambiente.is_set == false || scene->camera.is_set == false || scene->res.is_set == false)
	{
		ft_putendl_fd("Error: Mandatory scene file item is missing", STDERR_FILENO);
		return (ERROR);
	}
	return (0);
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
		if (line != NULL)
			free(line);
		line = get_next_line(fd);
		line_cnt++;
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (line[0] == '#' || line[0] == '\n' || line[0] == '\0')
			continue ;
		if (parsing(scene, line, line_cnt) != 0)
		{
			free(line);
			return (ERROR);
		}
	}
	free(line);
	return(check_must_haves(scene));
}