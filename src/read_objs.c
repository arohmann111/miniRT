/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:28:43 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 18:21:24 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_plane(t_scene *scene, char **split, int line_cnt)
{
	t_list	*new_elem;

	if (arrlen(split) != 4)
		return (print_error("Wrong plane input", line_cnt, split));
	new_elem = get_new_obj(PLANE);
	if (!new_elem)
		return (print_error("Plane obj can't be allocated", line_cnt, split));
	ft_lstadd_back(&scene->list, new_elem);
	if (get_vector(&((t_object *)new_elem->content)->pos, split[1],
			COORDINATES, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_vector(&((t_object *)new_elem->content)->pl.orient, split[2],
			ORIENTATION, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_colors(&((t_object *)new_elem->content)->colors, split[3],
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	ft_free_array(split);
	return (0);
}

int	get_sphere(t_scene *scene, char **split, int line_cnt)
{
	t_list	*new;
	int		error;

	error = 0;
	if (arrlen(split) != 4)
		return (print_error("Wrong sphere input", line_cnt, split));
	new = get_new_obj(SPHERE);
	if (!new)
		return (print_error("Sphere object can't be allocated",
				line_cnt, split));
	ft_lstadd_back(&scene->list, new);
	if (get_vector(&((t_object *)new->content)->pos, split[1],
			COORDINATES, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	((t_object *)new->content)->sp.diameter = ft_atod(split[2], &error);
	if (error == ERROR)
		return (print_error("Sphere diameter can't be converted",
				line_cnt, split));
	if (get_colors(&((t_object *)new->content)->colors, split[3],
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	ft_free_array(split);
	return (0);
}

int	get_cylinder(t_scene *scene, char **split, int line_cnt)
{
	t_vec3d	vec;
	t_vec3d	dir;
	t_vec3d	pos;
	double	height;
	int		error;

	error = 0;
	if (get_tube(scene, split, line_cnt) == ERROR)
		return (ERROR);
	if (get_vector(&vec, split[1], COORDINATES, line_cnt) == ERROR)
		return ((ERROR));
	if (get_vector(&dir, split[2], ORIENTATION, line_cnt) == ERROR)
		return (ERROR);
	height = ft_atod(split[4], &error);
	if (error == ERROR)
		return (print_error("Cylinder height can't be converted",
				line_cnt, NULL));
	pos = add_vec3d(vec, multi_vec3d(dir, height / 2.0));
	if (get_cy_circle(scene, split, line_cnt, pos) == ERROR)
		return (ERROR);
	pos = add_vec3d(vec, multi_vec3d(dir, height / -2.0));
	if (get_cy_circle(scene, split, line_cnt, pos) == ERROR)
		return (ERROR);
	ft_free_array(split);
	return (0);
}

static int	get_bowl_2(t_list *new, char **split, int line_cnt)
{
	int	error;

	error = 0;
	((t_object *)new->content)->bo.angle = ft_atod(split[3], &error);
	if (error == ERROR)
		return (print_error("Bowl angle can't be converted", line_cnt, split));
	if (check_range(0.0, 180.0, ((t_object *)new->content)->bo.angle) == false)
		return (print_error("Bowl angle is not in range [0.0,180.0]",
				line_cnt, split));
	error = 0;
	((t_object *)new->content)->bo.diameter = ft_atod(split[4], &error);
	if (error == ERROR)
		return (print_error("Bowl diameter can't be converted",
				line_cnt, split));
	if (get_colors(&((t_object *)new->content)->colors, split[5],
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	return (0);
}

int	get_bowl(t_scene *scene, char **split, int line_cnt)
{
	t_list	*new;

	if (arrlen(split) != 6)
		return (print_error("Wrong sphere input", line_cnt, split));
	new = get_new_obj(BOWL);
	if (!new)
		return (print_error("Bowl object can't be allocated", line_cnt, split));
	ft_lstadd_back(&scene->list, new);
	if (get_vector(&((t_object *)new->content)->pos, split[1],
			COORDINATES, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_vector(&((t_object *)new->content)->bo.orient, split[2],
			ORIENTATION, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_bowl_2(new, split, line_cnt) == ERROR)
		return (ERROR);
	ft_free_array(split);
	return (0);
}
