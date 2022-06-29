/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:39:33 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 18:52:42 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
		return (print_error("Ambient light ratio can't be converted",
				line_cnt, split));
	if (check_range(0.0, 1.0, ratio) == false)
		return (print_error("Ambient light ratio is not in range [0.0,1.0]",
				line_cnt, split));
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

int	get_camera(t_scene *scene, char **split, int line_cnt)
{
	int	error;

	error = 0;
	if (scene->camera.is_set == true)
		return (print_error("Camera already exists", line_cnt, split));
	if (arrlen(split) != 4)
		return (print_error("Wrong camera input", line_cnt, split));
	if (get_vector(&scene->camera.pos, split[1], COORDINATES,
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_vector(&scene->camera.orient, split[2], ORIENTATION,
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	scene->camera.fov = ft_atoi(split[3], &error);
	if (error == ERROR)
		return (print_error("Field of view can't be converted",
				line_cnt, split));
	if (check_range(1.0, 179.0, (double)scene->camera.fov) == false)
		return (print_error("Field of view is not in range [1-179]",
				line_cnt, split));
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

int	get_light(t_scene *scene, char **split, int line_cnt)
{
	t_list		*new_elem;
	int			error;

	error = 0;
	if (arrlen(split) != 4)
		return (print_error("Wrong light input", line_cnt, split));
	new_elem = get_new_l();
	if (!new_elem)
		return (print_error("Light can't be allocated", line_cnt, split));
	ft_lstadd_back(&scene->lights, new_elem);
	if (get_vector(&((t_light *)new_elem->content)->pos,
			split[1], COORDINATES, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	((t_light *)new_elem->content)->bright = ft_atod(split[2], &error);
	if (error == ERROR)
		return (print_error("Brightness ratio can't be converted",
				line_cnt, split));
	if (check_range(0.0, 1.0, ((t_light *)new_elem->content)->bright) == false)
		return (print_error("Brightness ratio is not in range [0.0,1.0]",
				line_cnt, split));
	if (get_colors(&((t_light *)new_elem->content)->colors, split[3],
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	ft_free_array(split);
	return (0);
}
