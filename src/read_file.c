/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:37:28 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 11:58:59 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
			return (print_error("Color is not in range [0-255]",
					line_cnt, colors));
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
		return (print_error("Wrong number of material factors",
				line_cnt, material));
	obj->matte = ft_atod(material[0], &error);
	if (error == ERROR)
		return (print_error("Matte material factor can't be converted",
				line_cnt, material));
	if (check_range(0.0, 1.0, obj->matte) == false)
		return (print_error("Material factor is not in range [0.0-1.0]",
				line_cnt, material));
	obj->spec = ft_atod(material[1], &error);
	if (error == ERROR)
		return (print_error("Specular material factor can't be converted",
				line_cnt, material));
	if (check_range(0.0, 1.0, obj->spec) == false)
		return (print_error("Material factor is not in range [0.0-1.0]",
				line_cnt, material));
	if (obj->matte + obj->spec != 1)
		return (print_error("Material factors must sum up to one",
				line_cnt, material));
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
		return (print_error("Wrong number of vector coordinates",
				line_cnt, vector));
	while (i < 3)
	{
		xyz[i] = ft_atod(vector[i], &error);
		if (error == ERROR)
			return (print_error("Vector can't be converted",
					line_cnt, vector));
		if (type == COORDINATES)
		{
			if (check_range(-500.0, 500.0, xyz[i]) == false)
				return (print_error(
						"Coordinate vector is not in range [-500.0,500.0]",
						line_cnt, vector));
		}
		else if (type == ORIENTATION)
		{
			if (check_range(-1000.0, 1000.0, xyz[i]) == false)
				return (print_error(
						"Orientation vector is not in range [-1000.0,1000.0]",
						line_cnt, vector));
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

int	parsing(t_scene *scene, char *line, int line_cnt)
{
	char	**split;

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
	return (check_must_haves(scene));
}
